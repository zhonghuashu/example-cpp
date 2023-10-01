#include <cstdio>
#include <cstdlib>

int main()
{
    char tmpname[L_tmpnam]; // usually around 20
    char *filename;
    const FILE *tmpfp;

    filename = ::tmpnam(tmpname);

    ::printf("Temporary file name is: %s\n", filename);

    tmpfp = ::tmpfile();
    if(tmpfp != nullptr)
    {
        ::printf("Opened a temporary file OK\n");
    }
    else
    {
        ::perror("tmpfile");
    }

    ::exit(0);
}
