#include "filesearch.h"

FileSearch::FileSearch(SearchOptions options, QObject *parent)
    : QObject(parent)
{
    this->options = options;
}

FileSearch::~FileSearch()
{
}
