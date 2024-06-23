/**
 * @file regio.h
 * @author Michael Hoffmann (michael.hoffmann@fh-dortmund.de)
 * @brief Register IO between the display controller and the MCU
 * @version 1.0
 * @date 2024-04-18
 *
 * @copyright Copyright (c) 2023, 2024
 *
 * From the HD44780 on the communication with the display controller
 * was done by accessing its Instruction Register (IR), Data Register
 * (DR) and Busy Flag Register (BF).  At the early days of the HD44780
 * there was only a parallel 4-bit/8-bit MPU interface.  Later the
 * communication could also be done by using SPI bus when using the
 * RW1073/SSD1803.  At the moment, the SSD1803A also supports the I2C
 * bus.
 *
 * So for communication the methods ir_write, dr_write, dr_read and
 * bfa_read must be implemented.
 * 
 * Implementing the SPI protocol makes RegIO depending on the
 * Espressif SPI library.
 */
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <Arduino.h>
#include <SPI.h>

/**
 * @brief Abstract interface for the SSD1803 bus interfaces
 * 
 * The SSD1803 display controller has a configurable communication
 * interface providing a 8/4 Bit parallel, an I2C (serial bus)
 * and a SPI (serial bus) interface.  RegIO is a collection
 * of member functions needed by the latter two serial bus
 * interfaces.
 * 
 * Q.v. [SSD1803A specs file](../ssd1803a_2_0.pdf)
 */
class RegIO {
public:
    virtual ~RegIO() = default;

    /**
     * @brief Writes a byte into the Instruction Register.
     * 
     * @param comd Command to be written
     * @return true Command has been written
     * @return false In case of failure
     */
    bool ir_write(uint8_t comd) const { return ir_write(&comd, 1); }

    /**
     * @brief Writes an array to the Instruction Register.
     * 
     * @param comd Command array
     * @param size Size of the array is 0 < size <= 80
     * @return true Commands have been written
     * @return false In case of failure
     */
    virtual bool ir_write(const void *comd, uint8_t size) const = 0;

    /**
     * @brief Test on busy flag is clear
     *
     */
    bool has_bf_clear() const { return (bfa_read() & 0x80) == 0; }

    /**
     * @brief Test on busy flag is set
     *
     */
    bool has_bf_set() const { return (bfa_read() & 0x80) != 0; }

    /**
     * @brief Return value of address counter
     *
     */
    bool address_read() const { return bfa_read() & 0x7f; }

    /**
     * @brief Read busy flag (DB7) and address counter (DB6 down to DB0)
     * 
     * @return uint8_t DB7, DB6..DB0
     */
    virtual uint8_t bfa_read() const = 0;

    /**
     * @brief Writes a byte into the Data Register.
     * 
     * @param data Data to be written
     * @return true Data has been written
     * @return false In case of failure
     */
    virtual bool dr_write(uint8_t data) const { return dr_write(&data, 1); }

    /**
     * @brief Writes an array to the Data Register.
     * 
     * @param src Data array
     * @param size Size of the array is 0 < size <= 80
     * @return true Data have been written
     * @return false In case of failure
     */
    virtual bool dr_write(const void *src, uint8_t size) const = 0;

    /**
     * @brief Reads an array from the Data Register
     * 
     * @param dst Data array
     * @param size Size of the array is 0 < size <= 80
     * @return true Data have been read
     * @return false In case of failure
     */
    virtual bool dr_read(void *dst, uint8_t size) const = 0;

protected:
    // IMHO almost 4-times of worst case delay time
    static constexpr unsigned long TIMEOUT_MS = 16;
    bool loop_until_ready() const;
};

/**
 * @brief I2C implementation of RegIO
 * 
 * TODO: Implement me.
 */
class __attribute__((unused)) I2COps : public RegIO {
public:

    /**
     * @brief Construct a new I2COps object
     * 
     * @param my_address The I2C address
     *
     * TODO: Implement me
     */
    explicit I2COps(uint8_t my_address);
    I2COps(const I2COps &) = delete;
    void operator=(const I2COps &) = delete;
    ~I2COps() override = default;

    bool ir_write(const void *comd, uint8_t size) const override;  // TODO: Implement me
    uint8_t bfa_read() const override;  // TODO: Implement me
    bool dr_write(const void *src, uint8_t size) const override;  // TODO: Implement me
    bool dr_read(void *dst, uint8_t size) const override;  // TODO: Implement me
};

/**
 * @brief SPI implementation of RegIO
 * 
 */
class SPIOps : public RegIO {
public:

    /**
     * @brief Construct a new SPIOps object
     * 
     * @param my_ss SS line
     * @param my_miso MISO line
     * @param my_mosi MOSI line
     * @param my_sck SCK line
     */
    SPIOps(int8_t my_ss, int8_t my_miso, int8_t my_mosi, int8_t my_sck);
    SPIOps(const SPIOps &) = delete;
    void operator=(const SPIOps &) = delete;

    ~SPIOps() override {
        pinMode(vspi->pinSS(), INPUT);
        vspi->end();
    }

    bool ir_write(const void *comd, uint8_t size) const override;
    uint8_t bfa_read() const override;
    bool dr_write(const void *src, uint8_t size) const override;
    bool dr_read(void *dst, uint8_t size) const override;

protected:
    static constexpr uint8_t EXECUTION_DELAY = 25;
    static constexpr uint32_t VSPI_CLOCK = 1e6;
    static constexpr uint8_t VSPI_BIT_ORDER = LSBFIRST;
    static constexpr uint8_t VSPI_DATA_MODE = SPI_MODE3;

private:
    std::unique_ptr<SPIClass> vspi{};
};
