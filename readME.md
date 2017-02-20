Kompilacja serwera:
1. W folderze /build wydaj komendę 'cmake ..'.
2. Then 'make'.
3. Start serwer with './httpServer'

Root folder dla serwera to /serverRoot.

Serwer działa na localhost na porcie 7070.

Uruchamianie testów:
1. W folderze /tests wydaj polecenie: cat 'nazwa_pliku_z_żądaniem' | nc localhost 7070.