## How do you test your file system work correctly? `FileSystemTest` could help you.

## Execution

```bash
C:\YourPath> FileSystemTest.exe C:\test_base_directory -t -d -s -f
```

```
Current directory path has been set as C:\test_base_directory
0x00002020[FILE_ATTRIBUTE_ARCHIVE, FILE_ATTRIBUTE_NOT_CONTENT_INDEXED]
The configuration was set to print duration.
The configuration was set to print time.
The configuration was set to print api statistics.
(Case1)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: Start.
[23:40:49.731] CreateFile IN
[23:40:49.731]              lpFileName = Case1test
[23:40:49.731]         dwDesiredAccess = 0x80000000[GENERIC_READ]
[23:40:49.732]             dwShareMode = 0x00000007[FILE_SHARE_READ, FILE_SHARE_WRITE, FILE_SHARE_DELETE]
[23:40:49.732]    lpSecurityAttributes = (NULL)
[23:40:49.732]   dwCreationDisposition = 2(CREATE_ALWAYS)
[23:40:49.732]    dwFlagsAndAttributes = 0x00000000
[23:40:49.732]           hTemplateFile = (NULL)
[23:40:49.732] CreateFile OUT
[23:40:49.732] return: (VALID_HANDLE)
[23:40:49.732] last error: 0(ERROR_SUCCESS)
[23:40:49.732] Duration: 0.000285661 second.
(MESSAGE) Deletion success.
(Case1)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: End. Success

(Case2)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: Start.
[23:40:49.734] CreateFile IN
[23:40:49.734]              lpFileName = Case2test
[23:40:49.734]         dwDesiredAccess = 0x80000000[GENERIC_READ]
[23:40:49.734]             dwShareMode = 0x00000007[FILE_SHARE_READ, FILE_SHARE_WRITE, FILE_SHARE_DELETE]
[23:40:49.734]    lpSecurityAttributes = (NULL)
[23:40:49.734]   dwCreationDisposition = 1(CREATE_NEW)
[23:40:49.734]    dwFlagsAndAttributes = 0x00000000
[23:40:49.734]           hTemplateFile = (NULL)
[23:40:49.734] CreateFile OUT
[23:40:49.734] return: (VALID_HANDLE)
[23:40:49.735] last error: 0(ERROR_SUCCESS)
[23:40:49.735] Duration: 0.00018816 second.
(MESSAGE) Deletion success.
(Case2)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: End. Success

(Case3)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: Start.
[23:40:49.736] CreateFile IN
[23:40:49.736]              lpFileName = Case3test
[23:40:49.736]         dwDesiredAccess = 0x80000000[GENERIC_READ]
[23:40:49.736]             dwShareMode = 0x00000007[FILE_SHARE_READ, FILE_SHARE_WRITE, FILE_SHARE_DELETE]
[23:40:49.736]    lpSecurityAttributes = (NULL)
[23:40:49.736]   dwCreationDisposition = 4(OPEN_ALWAYS)
[23:40:49.736]    dwFlagsAndAttributes = 0x00000000
[23:40:49.736]           hTemplateFile = (NULL)
[23:40:49.736] CreateFile OUT
[23:40:49.737] return: (VALID_HANDLE)
[23:40:49.737] last error: 0(ERROR_SUCCESS)
[23:40:49.737] Duration: 0.000183456 second.
(MESSAGE) Deletion success.
(Case3)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: End. Success

(Case4)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: Start.
[23:40:49.738] CreateFile IN
[23:40:49.738]              lpFileName = Case4test
[23:40:49.738]         dwDesiredAccess = 0x80000000[GENERIC_READ]
[23:40:49.738]             dwShareMode = 0x00000007[FILE_SHARE_READ, FILE_SHARE_WRITE, FILE_SHARE_DELETE]
[23:40:49.738]    lpSecurityAttributes = (NULL)
[23:40:49.738]   dwCreationDisposition = 3(OPEN_EXISTING)
[23:40:49.738]    dwFlagsAndAttributes = 0x00000000
[23:40:49.738]           hTemplateFile = (NULL)
[23:40:49.738] CreateFile OUT
[23:40:49.738] return: (INVALID_HANDLE)
[23:40:49.739] last error: 2(ERROR_FILE_NOT_FOUND)
[23:40:49.739] Duration: 7.22704e-005 second.
(ERROR) CreateFile
(MESSAGE) Deletion success(file not found).
(ERROR) Sub_CreateFile_Disposition
(Case4)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: End. Fail

(Case5)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: Start.
[23:40:49.739] CreateFile IN
[23:40:49.739]              lpFileName = Case5test
[23:40:49.740]         dwDesiredAccess = 0x80000000[GENERIC_READ]
[23:40:49.740]             dwShareMode = 0x00000007[FILE_SHARE_READ, FILE_SHARE_WRITE, FILE_SHARE_DELETE]
[23:40:49.740]    lpSecurityAttributes = (NULL)
[23:40:49.740]   dwCreationDisposition = 5(TRUNCATE_EXISTING)
[23:40:49.740]    dwFlagsAndAttributes = 0x00000000
[23:40:49.740]           hTemplateFile = (NULL)
[23:40:49.740] CreateFile OUT
[23:40:49.740] return: (INVALID_HANDLE)
[23:40:49.740] last error: 87(ERROR_INVALID_PARAMETER)
[23:40:49.740] Duration: 3.97701e-005 second.
(ERROR) CreateFile
(MESSAGE) Deletion success(file not found).
(ERROR) Sub_CreateFile_Disposition
(Case5)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: End. Fail

(Case6)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: Start.
[23:40:49.741] CreateFile IN
[23:40:49.741]              lpFileName = Case6test
[23:40:49.741]         dwDesiredAccess = 0x40000000[GENERIC_WRITE]
[23:40:49.742]             dwShareMode = 0x00000007[FILE_SHARE_READ, FILE_SHARE_WRITE, FILE_SHARE_DELETE]
[23:40:49.742]    lpSecurityAttributes = (NULL)
[23:40:49.742]   dwCreationDisposition = 2(CREATE_ALWAYS)
[23:40:49.742]    dwFlagsAndAttributes = 0x00000000
[23:40:49.742]           hTemplateFile = (NULL)
[23:40:49.742] CreateFile OUT
[23:40:49.742] return: (VALID_HANDLE)
[23:40:49.742] last error: 0(ERROR_SUCCESS)
[23:40:49.742] Duration: 0.000193719 second.
(MESSAGE) Deletion success.
(Case6)[Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]: End. Success
```
