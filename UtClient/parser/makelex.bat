
win_flex --wincompat clientcomvocab.l

lemon clientcomgrammer.y -s

powershell -Command "(gc clientcomgrammer.c) -replace 'clientcomgrammer.c', 'clientcomgrammer.cpp' | Out-File clientcomgrammer.cpp"

del clientcomgrammer.c