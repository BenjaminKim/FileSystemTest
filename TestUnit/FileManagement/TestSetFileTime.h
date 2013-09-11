#pragma once

void Test_SetFileTimeAll();
void Test_SetFileTime(const FILETIME* lpCreationTime,
                      const FILETIME* lpLastAccessTime,
                      const FILETIME* lpLastWriteTime);