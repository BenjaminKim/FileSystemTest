# FileSystemTest

Are you building your own filesystem?  
It is very difficult to test a filesystem.  
Don't worry. `FileSystemTest` will help you.

### Execution

```
FileSystemTest.exe [base_directory] [option] 
base_directory is mandatory it is the path where the tests will be runned
option list
#  -v [ --version ]          print the version number
#  -d [ --duration ]         print the api duration
#  -t [ --time ]             print the output with time as prefix of lines
#  -c [ --case ] arg         Run only the specified case.
#  -s [ --statistics ]       print api statistics
#  -f [ --full-log ]         print everything include utility functors.
#  -i [ --io-test ]          The program will run only for testing io performance.
#  -r [ --createfile-test ]  The program will run only for testing createfile.
#  -l [ --filelist-test ]    The program will run only for testing filelist.
#  -o [ --openfile-test ]    The program will run only for testing open files.
#  --starttime arg           The program will run on specified time.
#  --endtime arg             The program will run on specified time.
#  -q [ --quiet ]            print only test number and result in stdout (stderrstill have some detail) to compare results on 2 file system

```

## Basic Example

```bash
# `C:\test_base_directory` is a filesystem base directory you want to test.
# It can be a NTFS volume, or Windows network(SMB) or your own filesystem.
# (You need to mount your filesystem first.)
# In this example, it points a `NTFS` volume(C:)
C:\YourPath> FileSystemTest.exe C:\test_base_directory -t -d -s -f

# This command tries all APIs on the `NTFS` using all combinations of parameters and prints the results.
# The result of the API can be either success or failure. API fails doesn't mean the test failed.
# You should also run this test on your filesystem and compare it with NTFS's result using any `diff` tool you prefer.
# If the result is different, your file system is not NTFS compliant and applications will not work properly.

# If your file system is a network file system, it is better to compare it to the SMB(Windows Network Drive) rather than to NTFS.
```

## Result
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

# ...and hundred of test cases are omitted here.

# And it gives you a statistic for tested functions.
# You could measure how your file system fast.

Function Name : CreateDirectory
Min : 0.000292930330
Max : 0.000369049452
Sum : 0.000661979781
Count : 2
Operation per sec : 3,021.240310077520
Avg : 0.000330989891
StdDev : 0.000038059561

Function Name : CreateDirectoryEx
Min : 0.000197139974
Max : 0.000587143566
Sum : 0.063823745745
Count : 255
Operation per sec : 3,995.378162521441
Avg : 0.000250289199
StdDev : 0.000052711293

Function Name : RemoveDirectory
Min : 0.000094079814
Max : 0.000222370469
Sum : 0.000442602761
Count : 3
Operation per sec : 6,778.086956521739
Avg : 0.000147534254
StdDev : 0.000054513046

Function Name : CopyFile
Min : 0.000091941636
Max : 0.009981868254
Sum : 0.083748995057
Count : 20
Operation per sec : 238.808835694080
Avg : 0.004187449753
StdDev : 0.004236031032

Function Name : CopyFileEx
Min : 0.000085954739
Max : 0.009361796753
Sum : 0.063747626623
Count : 21
Operation per sec : 329.424028979674
Avg : 0.003035601268
StdDev : 0.004084865451

Function Name : CreateFile
Min : 0.000022664682
Max : 0.000303621218
Sum : 0.008617710953
Count : 75
Operation per sec : 8,703.007145692734
Avg : 0.000114902813
StdDev : 0.000077592803

Function Name : DeleteFile
Min : 0.000060724244
Max : 0.000205265048
Sum : 0.000695335352
Count : 7
Operation per sec : 10,067.084870848710
Avg : 0.000099333622
StdDev : 0.000048242309

Function Name : GetFileAttributes
Min : 0.000061151879
Max : 0.000516583705
Sum : 0.009245907528
Count : 116
Operation per sec : 12,546.091300124879
Avg : 0.000079706099
StdDev : 0.000041475734

Function Name : GetFileInformationByHandleEx
Min : 0.000035921383
Max : 0.000131711739
Sum : 0.001761430697
Count : 25
Operation per sec : 14,193.008011653314
Avg : 0.000070457228
StdDev : 0.000022356883

Function Name : GetFileSize
Min : 0.000035493748
Max : 0.000035493748
Sum : 0.000035493748
Count : 1
Operation per sec : 28,173.975903614457
Avg : 0.000035493748
StdDev : 0.000000000000

Function Name : GetFileSizeEx
Min : 0.000035493748
Max : 0.000035493748
Sum : 0.000035493748
Count : 1
Operation per sec : 28,173.975903614457
Avg : 0.000035493748
StdDev : 0.000000000000

Function Name : GetFileType
Min : 0.000029079215
Max : 0.000029079215
Sum : 0.000029079215
Count : 1
Operation per sec : 34,388.823529411762
Avg : 0.000029079215
StdDev : 0.000000000000

Function Name : SetFileAttributes
Min : 0.000086810010
Max : 0.000507175724
Sum : 0.016205247943
Count : 75
Operation per sec : 4,628.130360205832
Avg : 0.000216069973
StdDev : 0.000067332896

Function Name : MoveFile
Min : 0.000061151879
Max : 0.006358940148
Sum : 0.012365508630
Count : 30
Operation per sec : 2,426.103195462720
Avg : 0.000412183621
StdDev : 0.001110592118

Function Name : MoveFileEx
Min : 0.000048750449
Max : 0.008298267221
Sum : 0.053534407554
Count : 152
Operation per sec : 2,839.295454000816
Avg : 0.000352200050
StdDev : 0.000747844944

Function Name : SetFileInformationByHandle
Min : 0.000025658131
Max : 0.000765895212
Sum : 0.007700432767
Count : 30
Operation per sec : 3,895.884933636919
Avg : 0.000256681092
StdDev : 0.000166413330

Function Name : CreateDirectory
Min : 0.000157797506
Max : 0.000715861857
Sum : 0.067548451104
Count : 302
Operation per sec : 4,470.864913458009
Avg : 0.000223670368
StdDev : 0.000069670169

Function Name : RemoveDirectory
Min : 0.000051316262
Max : 0.000988693317
Sum : 0.088256273413
Count : 564
Operation per sec : 6,390.480565165561
Avg : 0.000156482754
StdDev : 0.000052658218

Function Name : ReadFile
Min : 0.000059868972
Max : 0.000415661723
Sum : 0.004417474898
Count : 63
Operation per sec : 14,261.541142303968
Avg : 0.000070118649
StdDev : 0.000044347422

Function Name : WriteFile
Min : 0.000049178085
Max : 0.001336360993
Sum : 0.063155351431
Count : 522
Operation per sec : 8,265.332836780995
Avg : 0.000120987263
StdDev : 0.000093946882

Function Name : CreateFile
Min : 0.000058586066
Max : 0.008014744873
Sum : 0.150909153111
Count : 716
Operation per sec : 4,744.576357639166
Avg : 0.000210766974
StdDev : 0.000325589034

Function Name : DeleteFile
Min : 0.000066283505
Max : 0.000561485435
Sum : 0.015803698192
Count : 60
Operation per sec : 3,796.579716419526
Avg : 0.000263394970
StdDev : 0.000088725795

Function Name : SetFileAttributes
Min : 0.000059868972
Max : 0.000371187629
Sum : 0.139102991738
Count : 843
Operation per sec : 6,060.257866971633
Avg : 0.000165009480
StdDev : 0.000048513022

Function Name : CloseHandle
Min : 0.000039342468
Max : 0.015926857221
Sum : 1.799948683738
Count : 714
Operation per sec : 396.677975572763
Avg : 0.002520936532
StdDev : 0.003741849575
```


#### Example integrated in a tests suite
> 
C:\YourPath> FileSystemTest.exe C:\test_base_directory -q

```
Current directory path has been set as C:\test_base_directory
0x00002020[FILE_ATTRIBUTE_ARCHIVE, FILE_ATTRIBUTE_NOT_CONTENT_INDEXED]
(Case 00001) OK [Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]
(Case 00002) OK [Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]
(Case 00003) OK [Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]
(Case 00004) KO [Calling CreateFile with dwDesiredAccess, dwCreateDisposition.]
...
```
