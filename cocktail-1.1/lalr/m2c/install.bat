mkdir %lib%\lalr
copy lalr.bat %bin%
copy lalr %lib%\lalr
cd ..\lib
copy e*.* %lib%\lalr
copy p*.* %lib%\lalr
copy s*.* %lib%\lalr
