create database gunStore;
use gunStore;

create table category(
	id_category TINYINT auto_increment primary key,
    c_name VARCHAR(20) not null unique
) character set utf8;
create index categoryName on category(c_name);

create table product(
	id_product MEDIUMINT UNSIGNED auto_increment primary key,
    p_name VARCHAR(100) not null,
    p_priceOne DECIMAL(8, 2) not null,
    p_count INT not null DEFAULT 0,
    p_brand VARCHAR(40),
    p_weight FLOAT,
    p_package VARCHAR(40),
    p_country VARCHAR(30) not null,
    id_category TINYINT,
    isDelete BOOLEAN not null DEFAULT 0,
    constraint FK_category foreign key(id_category) references category(id_category) ON DELETE CASCADE ON UPDATE CASCADE
) character set utf8;
create index productName on product(p_name);
create index productPackage on product(p_package);

create table characteristic(
	id_characteristic int auto_increment primary key,
    charact_name VARCHAR(20) not null unique
) character set utf8;
create index characteristicName on characteristic(charact_name);

create table categoryCharacteristic(
	id_categoryCharacteristic INT auto_increment primary key,
    id_category TINYINT,
    id_characteristic INT,
    constraint FK_idCategory foreign key(id_category) references category(id_category) ON DELETE CASCADE ON UPDATE CASCADE,
    constraint FK_characteristic foreign key(id_characteristic) references characteristic(id_characteristic) ON DELETE CASCADE ON UPDATE CASCADE
) character set utf8;

create table productValue(
	id_productValue INT auto_increment primary key,
    id_product MEDIUMINT UNSIGNED,
    id_categoryCharacteristic INT,
    `value` VARCHAR(60),
    constraint FK_product foreign key(id_product) references product(id_product) ON DELETE CASCADE ON UPDATE CASCADE,
    constraint FK_categoryCharacteristic foreign key(id_categoryCharacteristic) references categoryCharacteristic(id_categoryCharacteristic) ON DELETE CASCADE ON UPDATE CASCADE
) character set utf8;

create table address(
	id_address INT auto_increment primary key,
    city VARCHAR(25) not null,
    details VARCHAR(80)
) character set utf8;
create index details on address(details);

create table buyer(
	inn VARCHAR(10) primary key,
    full_name VARCHAR(60) not null,
    phone_number varchar(10) not null,
    email VARCHAR(40),
    id_address INT,
    license INT(7) not null,
    constraint FK_address foreign key(id_address) references address(id_address) ON DELETE CASCADE ON UPDATE CASCADE
) character set utf8;
create index buyerFullName on buyer(full_name);

create table worker(
	id_worker TINYINT auto_increment primary key,
    w_full_name VARCHAR(60) not null unique,
    `position` ENUM('Адміністратор', 'Продавець') not null,
    w_phoneNum varchar(10) not null,
    w_address VARCHAR(80) not null,
    gender ENUM('Чоловік', 'Жінка') not null,
    birthday DATE,
    isDelete BOOLEAN not null DEFAULT 0
) character set utf8;
create index workerFullName on worker(w_full_name);

create table sales(
	id_sales INT auto_increment primary key,
    inn VARCHAR(10),
    id_worker TINYINT,
    date_time DATETIME not null,
    constraint FK_inn foreign key(inn) references buyer(inn) ON DELETE CASCADE ON UPDATE CASCADE,
    constraint FK_idWorker foreign key(id_worker) references worker(id_worker) ON DELETE CASCADE ON UPDATE CASCADE
) character set utf8;

create table listProduct(
	id_listProduct INT auto_increment primary key,
    id_sales INT,
    id_product MEDIUMINT UNSIGNED,
    listP_count INT not null,
    constraint FK_idSales foreign key(id_sales) references sales(id_sales) ON DELETE CASCADE ON UPDATE CASCADE,
    constraint FK_idProduct foreign key(id_product) references product(id_product) ON DELETE CASCADE ON UPDATE CASCADE
) character set utf8;

create table supplier(
	id_supplier TINYINT auto_increment primary key,
    sup_name VARCHAR(60) not null unique,
    sup_edrpou INT(8) not null unique,
    sup_phoneNum varchar(10) not null,
    sup_address VARCHAR(60) not null,
    sup_bank VARCHAR(16) not null unique,
    isDelete BOOLEAN not null DEFAULT 0
) character set utf8;
create index supplierName on supplier(sup_name);
create index supplierEdrpou on supplier(sup_edrpou);

create table waybill(
	id_waybill INT auto_increment primary key,
    id_worker TINYINT,
    id_supplier TINYINT,
    waybillDate DATE not null,
    constraint FK_waybillIdWorker foreign key(id_worker) references worker(id_worker) ON DELETE CASCADE ON UPDATE CASCADE,
    constraint FK_idSupplier foreign key(id_supplier) references supplier(id_supplier) ON DELETE CASCADE ON UPDATE CASCADE
) character set utf8;

create table listSupply(
	id_listSupply INT auto_increment primary key,
    id_waybill INT,
    id_product MEDIUMINT UNSIGNED,
    listS_priceCount DOUBLE(8, 2) not null,
    listS_count INT not null,
    constraint FK_idWaybill foreign key(id_waybill) references waybill(id_waybill) ON DELETE CASCADE ON UPDATE CASCADE,
    constraint FK_listSIdProduct foreign key(id_product) references product(id_product) ON DELETE CASCADE ON UPDATE CASCADE
) character set utf8;