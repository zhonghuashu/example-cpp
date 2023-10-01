/**
 * @file mmap.cpp
 * @brief Create and define a RECORD structure, map to memory.
 * @author Shu, Zhong Hua
 * @date 2023-06-02
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

namespace {

typedef struct
{
    int integer;
    char string[24];
} RECORD;

#define NRECORDS (100)

}

int main()
{
    RECORD record, *mapped;
    int f;
    FILE *fp;

    if (nullptr == (fp = ::fopen("records.dat", "w+")))
    {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NRECORDS; i++)
    {
        record.integer = i;
        ::sprintf(record.string, "RECORD-%d", i);
        ::fwrite(&record, sizeof(record), 1, fp);
    }
    ::fclose(fp);

    /*  We now change the integer value of record 43 to 143
        and write this to the 43rd record's string.  */
    fp = ::fopen("records.dat", "r+");
    ::fseek(fp, 43 * sizeof(record), SEEK_SET);
    ::fread(&record, sizeof(record), 1, fp);
    std::cout << "Record: " << record.integer << ", " << record.string << "\n";

    record.integer = 143;
    ::sprintf(record.string, "RECORD-%d", record.integer);

    ::fseek(fp, 43 * sizeof(record), SEEK_SET);
    ::fwrite(&record, sizeof(record), 1, fp);
    ::fclose(fp);

    /*  We now map the records into memory
        and access the 43rd record in order to change the integer to 243
        (and update the record string), again using memory mapping.  */

    // Avoid TOCTOU vulnerabilities
    fp = ::fopen("records.dat", "r+");
    if (nullptr == fp)
    {
        return EXIT_FAILURE;
    }
    f = ::fileno(fp);
    mapped = (RECORD *)::mmap(nullptr, NRECORDS * sizeof(record), PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);

    std::cout << "Record: " << mapped[43].integer << ", " << mapped[43].string << "\n";

    mapped[43].integer = 243;
    ::sprintf(mapped[43].string, "RECORD-%d", mapped[43].integer);
    ::msync((void *)mapped, NRECORDS * sizeof(record), MS_ASYNC);
    ::munmap((void *)mapped, NRECORDS * sizeof(record));
    ::close(f);

    if (::unlink("records.dat") < 0)
    {
        ::perror("Delete out file failed");
    }

    ::exit(EXIT_SUCCESS);
}

