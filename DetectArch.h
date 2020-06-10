#include <iostream>
#include <stdint.h>
#include <string>
#include <bits/stdc++.h> 
using namespace std;

// Standard 'Elf64Hdr' header structure from Linux Foundation : https://github.com/torvalds/linux/blob/master/include/uapi/linux/elf.h 
// Machine type (code) for each of library arch, Linux Foundation : https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.eheader.html 

struct Elf64Hdr {
	uint8_t     e_ident[16];
	uint16_t    e_type;              /* Object file type */
	uint16_t    e_machine;           /* Architecture */
	uint32_t    e_version;           /* Object file version */
	uint64_t    e_entry;             /* Entry point virtual address */
	uint64_t    e_phoff;             /* Program header table file offset */
	uint64_t    e_shoff;             /* Section header table file offset */
	uint32_t    e_flags;             /* Processor-specific flags */
	uint16_t    e_ehsize;            /* ELF header size in bytes */
	uint16_t    e_phentsize;         /* Program header table entry size */
	uint16_t    e_phnum;             /* Program header table entry count */
	uint16_t    e_shentsize;         /* Section header table entry size */
	uint16_t    e_shnum;             /* Section header table entry count */
	uint16_t    e_shstrndx;          /* Section header string table index */
} ;
static int firstCall = 1;   

void DetectFileArch(const char* elfFile) {
	struct Elf64Hdr elfheader;
	FILE* file = fopen(elfFile, "rb");
	if (file) {
		// read the header
		fread(&elfheader, 1, sizeof(elfheader), file);
		//cout<<elfheader.e_type<<endl<<elfheader.e_ident[1]<<endl<<elfheader.e_ident[2]<<endl<<elfheader.e_ident[3]<<endl;
		if (elfheader.e_ident[1] == 'E' && elfheader.e_ident[2] == 'L' && elfheader.e_ident[3] == 'F') 
		{
			//Extracting the file name
			string elfFileStr = elfFile;
			reverse(elfFileStr.begin(),elfFileStr.end());
			size_t pos = elfFileStr.find("/");
			elfFileStr = elfFileStr.substr (0,pos);
			reverse(elfFileStr.begin(),elfFileStr.end());
			
			// write the classified type of library arch to the output file
			FILE* fout = NULL;
			if(firstCall == 1)
			{
				fout = fopen("results.txt", "wb");
				firstCall++;
			}
			else
				fout = fopen("results.txt", "a");
			if (NULL != fout) {
			    fseek (fout, 0, SEEK_END);
			    int size = ftell(fout);
			    rewind(fout);
			    if (0 == size) {
			    	char dataToAppend[] = "File\t\t\t\t\tArchType\n======\t\t\t\t\t=========\n";
			    	fputs(dataToAppend, fout);  
			    }
			}
			switch(elfheader.e_machine)
			{
				case(3):
					{
						elfFileStr = elfFileStr + "\t\t\tX86\n";
						const char *c = elfFileStr.c_str();
				    	fputs(c, fout);
				    	break;
				    }
			    case(8):
			    	{
						elfFileStr = elfFileStr + "\t\t\tMIPS\n";
						const char *c = elfFileStr.c_str();
				    	fputs(c, fout);
				    	break;
				    }
				case(40):
					{
						elfFileStr = elfFileStr + "\t\t\tARMV7ABI\n";
						const char *c = elfFileStr.c_str();
				    	fputs(c, fout);
				    	break;
				    }
				case(62):
					{
						elfFileStr = elfFileStr + "\t\t\tX86_64\n";
						const char *c = elfFileStr.c_str();
				    	fputs(c, fout);
				    	break;
				    }
			    case(183):
			    	{
						elfFileStr = elfFileStr + "\t\t\tARM64_V8\n";
						const char *c = elfFileStr.c_str();
				    	fputs(c, fout);
				    	break;
				    }
			    case(164):
					{
						elfFileStr = elfFileStr + "\t\t\tARMABI\n";
						const char *c = elfFileStr.c_str();
				    	fputs(c, fout);
				    	break;
				    }
			}
			fclose(fout);
		}

		// finally close the file
		fclose(file);
	}
}
