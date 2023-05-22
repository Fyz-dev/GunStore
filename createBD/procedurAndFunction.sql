delimiter //
create procedure getCharacteristicForProduct(productId int)
begin
	select charact_name, `value`, id_productValue from productvalue
    join categorycharacteristic using(id_categoryCharacteristic) join characteristic using(id_characteristic) where id_product = productId;
end; //

delimiter //
create procedure getMainCharacteristicForProduct(productName varchar(100))
begin
	select id_product, p_name, p_count, p_brand, p_weight, p_package, p_country , c_name, p_priceOne
    from product join category using(id_category) where p_name = productName;
end; //

delimiter //
create procedure addCountProduct(idProduct int, count int)
begin
	UPDATE product SET p_count = p_count + count where id_product = idProduct ;
end; //

delimiter //
create procedure getAllProduct()
begin
	select p_name as 'Назва', p_priceOne as 'Ціна(грн.)', p_count as 'Кількість(шт.)', p_brand as 'Бренд', p_weight as 'Вес(г.)',p_package as 'Упаковка', p_country as 'Країна', c_name as 'Категорія' 
    from product join category using(id_category);
end; //

delimiter //
create procedure getCharacteristicForCategory(nameCategory varchar(20))
begin
	select charact_name from category join categorycharacteristic using(id_category) join characteristic using(id_characteristic) where c_name = nameCategory;
end; //

#-------------------------------------------------------------------------------------------------------------------
#ДЛЯ ПОЛЬЗОВАТЕЛЕЙ !!!ИСПОЛЬЗОВАТЬ СОЗДАНИЕ ПОЛЬЗОВАТЕЛЕЙ ТОЛЬКО ЧЕРЕЗ ПРОЦЕДУРУ!!!
delimiter //
create procedure createCasir(FIO varchar(60), passwordd varchar(60))
begin
    SET @sql = CONCAT('CREATE USER "', FIO, '"@"localhost" IDENTIFIED BY "', passwordd, '"DEFAULT ROLE casir');
    PREPARE stmt FROM @sql;
    EXECUTE stmt;
    DEALLOCATE PREPARE stmt;
end; //

delimiter //
create procedure createAdmin(FIO varchar(60), passwordd varchar(60))
begin
    SET @sql = CONCAT('CREATE USER "', FIO, '"@"localhost" IDENTIFIED BY "', passwordd, '"DEFAULT ROLE admins');
    PREPARE stmt FROM @sql;
    EXECUTE stmt;
    DEALLOCATE PREPARE stmt;
end; //

delimiter //
create procedure dropUser(id int)
begin
    SET @sql = CONCAT('DROP USER "', (select w_full_name from worker where id_worker = id), '"@"localhost"');
    PREPARE stmt FROM @sql;
    EXECUTE stmt;
    DEALLOCATE PREPARE stmt;
    
    DELETE FROM worker where id_worker = id;
end; //

delimiter //
create procedure deactivationUser(id int)
begin
    SET @sql = CONCAT('DROP USER "', (select w_full_name from worker where id_worker = id), '"@"localhost"');
    PREPARE stmt FROM @sql;
    EXECUTE stmt;
    DEALLOCATE PREPARE stmt;
end; //
#-------------------------------------------------------------------------------------------------------------------