#include "Hash.h"

Hash hashClass;
int main()
{

	//First part gets the HDD informations
	std::cout << "Please send this information to NAGA" << std::endl;
	std::cout << "Make sure to have this program opened on your main machine where you play Rust. Otherwise wrong HWID will be gathered which will cause many issues." << std::endl;
	std::cout << "\n";

	TCHAR volumeName[MAX_PATH + 1] = { 0 };
	TCHAR fileSystemName[MAX_PATH + 1] = { 0 };
	DWORD serialNumber = 0;
	DWORD maxComponentLen = 0;
	DWORD fileSystemFlags = 0;
	if (GetVolumeInformation(
		_T("C:\\"),
		volumeName,
		ARRAYSIZE(volumeName),
		&serialNumber,
		&maxComponentLen,
		&fileSystemFlags,
		fileSystemName,
		ARRAYSIZE(fileSystemName)))
	{
		//std::cout << "Volume Name: " << volumeName << std::endl;
		//std::cout << "HDD Serial: " << serialNumber << std::endl;
		//std::cout << "File System Type: " << fileSystemName << std::endl;
		//std::cout << "Max Component Length: " << maxComponentLen << std::endl;
	}
	//Second part gets the computer name
	TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(computerName) / sizeof(computerName[0]);
	if (GetComputerName(
		computerName,
		&size))
	{
		std::cout << "Computer Name: " << computerName << std::endl;
	}

	
	//CPU hash
	int cpuinfo[4] = { 0, 0, 0, 0 };				//EAX, EBX, ECX, EDX
	__cpuid(cpuinfo, 1);
	unsigned int hash = 0;
	unsigned int* ptr = (unsigned int*)(&cpuinfo[0]);
	for (char32_t i = 0; i < 8; i++)
		hash += ptr[i];
	//std::cout << "CPU Hash: " << hash << std::endl;

	std::string info = "c" + std::to_string(hash) + "s" + std::to_string(serialNumber) + "m" + std::to_string(maxComponentLen);

	

	std::cout << "\nOriginal:  " << info << std::endl;
	std::cout << "Encrypted: " << hashClass.EncryptMessage(info) << std::endl;
	std::cout << "Decrypted: " << hashClass.DecryptMessage(hashClass.EncryptMessage(info)) << std::endl << std::endl;

	//Get the IP address
	
	system("pause");
	return(0);
}



