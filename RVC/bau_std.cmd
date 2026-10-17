@echo off

IF ["%~1"]==["clean"] (
	SET "wnos=-Wno-int-to-pointer-cast -Wno-strict-aliasing -Wno-maybe-uninitialized"
) ELSE (
	SET "wnos="
)

gcc main.c rvfile.c -o output\main.exe -O3 -mcpu=native -march=native -mtune=native -Wall -Wextra %wnos% -std=c23