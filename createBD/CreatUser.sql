#Роли
CREATE ROLE casir;
GRANT SELECT, UPDATE ON gunstore.* TO casir;
GRANT INSERT ON gunstore.buyer TO casir;
GRANT INSERT ON gunstore.sales TO casir;
GRANT INSERT ON gunstore.address TO casir;
GRANT INSERT ON gunstore.listproduct TO casir;
GRANT INSERT ON gunstore.waybill TO casir;
GRANT INSERT ON gunstore.listsupply TO casir;
GRANT EXECUTE ON gunstore.* TO casir;
DROP ROLE casir;

CREATE ROLE admins;
GRANT ALL PRIVILEGES ON gunstore.* TO admins WITH GRANT OPTION;
GRANT CREATE USER ON *.* TO admins;
DROP ROLE admins;

call createAdmin('Вертухайло Олег Петрович', 1111);
