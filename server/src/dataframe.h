#ifndef DATAFRAME_H
#define DATAFRAME_H

/**
 * type for a page
 * @def typedef char page_t[PAGE_ROWS][PAGE_COLUMNS +1];
 * @def PAGE_ROWS 4
 * @def PAGE_COLUMNS 20 + 1 (for null terminator)
 */
typedef char page_t[4][21];

/**
 * type for a dataframe
 */
typedef struct {
    int pageNumber;
    page_t pageContent;
} dataframe;

#endif
