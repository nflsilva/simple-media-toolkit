#include "cutil/filesystem.h"

#ifdef _WIN32
DIR* opendir(const char* name) {
    DIR* dir = (DIR*)malloc(sizeof(DIR));
    if (!dir) return NULL;
    
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*", name); // Append '\*' for directory searching
    
    dir->hFind = FindFirstFile(searchPath, &dir->findFileData);
    if (dir->hFind == INVALID_HANDLE_VALUE) {
        free(dir);
        return NULL;
    }
    return dir;
}

struct dirent* readdir(DIR* dir) {
    if (dir->hFind == INVALID_HANDLE_VALUE)
        return NULL;

    strncpy(dir->direntry.d_name, dir->findFileData.cFileName, MAX_PATH);
    
    if (!FindNextFile(dir->hFind, &dir->findFileData)) {
        if (GetLastError() == ERROR_NO_MORE_FILES) {
            FindClose(dir->hFind);
            dir->hFind = INVALID_HANDLE_VALUE;
        }
        return NULL;
    }
    
    return &dir->direntry;
}

int closedir(DIR* dir) {
    if (dir == NULL) return -1;
    if (dir->hFind != INVALID_HANDLE_VALUE)
        FindClose(dir->hFind);
    free(dir);
    return 0;
}
#endif


CUTILFileBrowser* cutilFileBrowserInit(const char* directoryPath, const char* fileExtension)
{
    CUTILFileBrowser* browser = (CUTILFileBrowser*) malloc(sizeof(CUTILFileBrowser));
    browser->directoryContentsSize = 0;
    strcpy(browser->directoryPathBuffer, directoryPath);
    sprintf(browser->fileExtensionBuffer, ".%s", fileExtension);
    cutilFileBrowserLoadDirectoryContents(browser);
    return browser;
}

void cutilFileBrowserDestroy(CUTILFileBrowser* fileBrowser)
{
    if(!fileBrowser) return;
    free(fileBrowser);
}

char* cutilFileBrowserSelectItem(CUTILFileBrowser* fileBrowser, int itemIndex)
{
    if(!fileBrowser || itemIndex < 0 || itemIndex >= fileBrowser->directoryContentsSize) 
        return NULL;

    CUTILFilesystemItem* item = &fileBrowser->directoryContents[itemIndex];

    if(item->isDirectory)
    {
        // TODO: I should create a cross-platform component to deal with
        // file paths
        strcat(fileBrowser->directoryPathBuffer, "/");
        strcat(fileBrowser->directoryPathBuffer, item->name);
        cutilFileBrowserLoadDirectoryContents(fileBrowser);
        return NULL;
    }

    strcpy(fileBrowser->selectedItemPathBuffer, fileBrowser->directoryPathBuffer);
    strcat(fileBrowser->selectedItemPathBuffer, "/");
    strcat(fileBrowser->selectedItemPathBuffer, item->name);
    for(int i = 0; i < fileBrowser->directoryContentsSize; i++) 
        fileBrowser->directoryContents[i].isSelected = 0;

    item->isSelected = 1;
    return fileBrowser->selectedItemPathBuffer;
}

static int filesystemItemComparator(const void* a, const void* b) 
{
    return strcmp(((CUTILFilesystemItem*)a)->name, ((CUTILFilesystemItem*)b)->name);
}

static int fileHasExtension(CUTILFileBrowser* fileBrowser, char* itemName)
{
    int fileNameLength = strlen(itemName);
    int extensionLength = strlen(fileBrowser->fileExtensionBuffer);

    for(int i = 0; i < extensionLength; i++)
        if(fileBrowser->fileExtensionBuffer[extensionLength - i] != itemName[fileNameLength - i])
            return 0;
    return 1;
}

void cutilFileBrowserLoadDirectoryContents(CUTILFileBrowser* fileBrowser)
{
    if(!fileBrowser) return;

	DIR* pdir = opendir(fileBrowser->directoryPathBuffer);
	if (!pdir) return;
    
    fileBrowser->directoryContentsSize = 0;
    struct dirent* pent;
    while ((pent = readdir(pdir)) != NULL) 
    {
        CUTILFilesystemItem* item = &fileBrowser->directoryContents[fileBrowser->directoryContentsSize];

        // ignore self
        if(strcmp(pent->d_name, ".") == 0) continue;

        int isDirectory = pent->d_type == DT_DIR;
        if(!isDirectory && !fileHasExtension(fileBrowser, pent->d_name)) continue;

        strcpy(item->name, pent->d_name);
        item->isDirectory = isDirectory;
        item->isSelected = 0;
        fileBrowser->directoryContentsSize++;
    }
    closedir(pdir);

    // sort items for convenience
    cutilSortMergeSort(
        fileBrowser->directoryContents, 
        sizeof(CUTILFilesystemItem),
        fileBrowser->directoryContentsSize,
        &filesystemItemComparator
    );
}

const char* cutilFileBrowserLoadFile(const char* filePath)
{
    FILE *file = NULL;
    file = fopen(filePath, "r");
    if(!file) return NULL;

    unsigned long readSize = 0;
    unsigned long contentSize = 0;
    unsigned long fileContentBufferSize = CUTIL_FS_READ_CHUNK_SIZE * 10;
    char* fileContentBuffer = (char*)malloc(sizeof(char) * (fileContentBufferSize + 1));
    int didError = 0;
    do 
    {
        readSize = fread(&fileContentBuffer[contentSize], sizeof(char), CUTIL_FS_READ_CHUNK_SIZE, file);
        if (ferror(file)) 
        {
            didError = 1;
            break;
        }

        contentSize += readSize;
        if(contentSize == fileContentBufferSize) 
        {
            fileContentBufferSize = fileContentBufferSize + CUTIL_FS_READ_CHUNK_SIZE * 10;
            char* newContent = realloc(fileContentBuffer, fileContentBufferSize);
            if(!newContent)
            {
                didError = 1;
                break;
            }
            fileContentBuffer = newContent;
        }
            
    } while (readSize == CUTIL_FS_READ_CHUNK_SIZE);

    fclose(file);
    if(didError)
    {
        free(fileContentBuffer);
        return NULL;
    }

    fileContentBuffer[contentSize] = '\0';    
    return fileContentBuffer;
}
