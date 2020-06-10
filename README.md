# BlueS

The program takes one command line argument of the path where the files to be validated are present. 

To execute :
1. cd to the Directory with BlueS.exe.
2. Execute BlueS.exe with /path/to/location/
eg :
    "BlueS.exe C:\personal\BlueS\test-input\"

The programs prints the results as :
    '''		

		Total number of libraries: 6
		File                                    ArchType
		======                                  =========
		libanw.14.so                            armeabi-v7a
		libanw.18.so                            x86
		libARMClientService_arm64-v8a.so                                arm64-v8a
		libiomx.13.so                           mips
		libjniloader.so                         x86_64
		libudev.so                              armeabi-v7a

    '''
Note: In case the exe is ran without giving any path as argument. 
It assumes a default path of "current_directory/test-input/" and prints an extra line notice as "No Command Line Path given, taking default "test-input/" Directory"

References to understand the ELF File headers were taken from Linux foundation

// Standard 'Elf64Hdr' header structure from Linux Foundation : https://github.com/torvalds/linux/blob/master/include/uapi/linux/elf.h

// Machine type (code) for each of library arch, Linux Foundation : https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.eheader.html 
	
    https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
