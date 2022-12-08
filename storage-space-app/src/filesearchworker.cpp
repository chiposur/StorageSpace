#include "filesearch.h"
#include "filesearchworker.h"

void FileSearchWorker::search(SearchOptions options)
{
    FileSearch fs(options, this);
    emit resultsReady(fs.run());
}
