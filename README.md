tesis-jaks
==========

Dependencies
git (opcional)
g++ (compilador)
cmake (automatizador para compilar)
mysql (mariadb-server mariadb-client) (base de datos)
libboost-all-dev (libreria para usar matrices)
libboost-log1.58-dev libboost-program-options-dev libboost-thread-dev libboost-math-dev
qt5-default libqt5sql5-mysql (conector para la bd mysql)
libmysqlcppconn-dev libmysqlcppconn7 (conector para la bd mysql) --deprecated

./tesis-jaks --option 1 --algorithm RandomBOBO --strategy RANK_BY_INTRA_INTER --element ARTICLE --bundles 10 --budget 5 --gamma 0.1 --produce 10 --iteration 100  --print 1 --write 1
