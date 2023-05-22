use gunstore;

select * from characteristic join categorycharacteristic using(id_characteristic) join category using(id_category);

#Категорії
INSERT INTO category VALUES(1, 'Вогнепальна');
INSERT INTO category VALUES(2, 'Травматична');
INSERT INTO category VALUES(3, 'Пневматична');
INSERT INTO category VALUES(4, 'Холодна');
INSERT INTO category VALUES(5, 'Набої');

#Характеристики
INSERT INTO characteristic VALUES(1, 'Калібр');
INSERT INTO characteristic VALUES(2, 'Кількість в пачці');
INSERT INTO characteristic VALUES(3, 'Матеріал леза');
INSERT INTO characteristic VALUES(4, 'Товщина леза');
INSERT INTO characteristic VALUES(5, 'Довжина леза');
INSERT INTO characteristic VALUES(6, 'Довжина ствола');
INSERT INTO characteristic VALUES(7, 'Загальна довжина');
INSERT INTO characteristic VALUES(8, 'Ємність магазину');
INSERT INTO characteristic VALUES(9, 'Матеріал рукоятки');
INSERT INTO characteristic VALUES(10, 'Матеріал ложи');
INSERT INTO characteristic VALUES(11, 'Колір ложи');
INSERT INTO characteristic VALUES(12, 'Матеріал ствола');
INSERT INTO characteristic VALUES(13, 'Дульна різьба');
INSERT INTO characteristic VALUES(14, 'Твіст ствола');
INSERT INTO characteristic VALUES(15, 'Об\'єм резервуару');
INSERT INTO characteristic VALUES(16, 'Енергія (Дж)');

#Категорія-Характеристика
INSERT INTO categorycharacteristic VALUES(1, 1, 1);
INSERT INTO categorycharacteristic VALUES(2, 1, 6);
INSERT INTO categorycharacteristic VALUES(3, 1, 7);
INSERT INTO categorycharacteristic VALUES(4, 1, 8);
INSERT INTO categorycharacteristic VALUES(5, 1, 9);
INSERT INTO categorycharacteristic VALUES(6, 1, 10);
INSERT INTO categorycharacteristic VALUES(7, 1, 11);
INSERT INTO categorycharacteristic VALUES(8, 1, 12);
INSERT INTO categorycharacteristic VALUES(9, 1, 13);
INSERT INTO categorycharacteristic VALUES(10, 1, 14);

INSERT INTO categorycharacteristic VALUES(11, 2, 1);
INSERT INTO categorycharacteristic VALUES(12, 2, 6);
INSERT INTO categorycharacteristic VALUES(13, 2, 7);
INSERT INTO categorycharacteristic VALUES(14, 2, 8);
INSERT INTO categorycharacteristic VALUES(15, 2, 9);
INSERT INTO categorycharacteristic VALUES(16, 2, 10);
INSERT INTO categorycharacteristic VALUES(17, 2, 11);
INSERT INTO categorycharacteristic VALUES(18, 2, 12);
INSERT INTO categorycharacteristic VALUES(19, 2, 13);
INSERT INTO categorycharacteristic VALUES(20, 2, 14);

INSERT INTO categorycharacteristic VALUES(21, 3, 1);
INSERT INTO categorycharacteristic VALUES(22, 3, 6);
INSERT INTO categorycharacteristic VALUES(23, 3, 7);
INSERT INTO categorycharacteristic VALUES(24, 3, 8);
INSERT INTO categorycharacteristic VALUES(25, 3, 9);
INSERT INTO categorycharacteristic VALUES(26, 3, 10);
INSERT INTO categorycharacteristic VALUES(27, 3, 11);
INSERT INTO categorycharacteristic VALUES(28, 3, 12);
INSERT INTO categorycharacteristic VALUES(29, 3, 15);
INSERT INTO categorycharacteristic VALUES(30, 3, 16);

INSERT INTO categorycharacteristic VALUES(31, 4, 3);
INSERT INTO categorycharacteristic VALUES(32, 4, 4);
INSERT INTO categorycharacteristic VALUES(33, 4, 5);
INSERT INTO categorycharacteristic VALUES(34, 4, 7);
INSERT INTO categorycharacteristic VALUES(35, 4, 9);

INSERT INTO categorycharacteristic VALUES(36, 5, 1);
INSERT INTO categorycharacteristic VALUES(37, 5, 2);
INSERT INTO categorycharacteristic VALUES(38, 5, 16);

#Товар
INSERT INTO product VALUES(1, 'MLKWSK-MARS', 286360, 10, 'Lewis Machine and Tool Company', 4650, 'Картонна коробка', 'Чехія', 1);
INSERT INTO product VALUES(2, 'XCR-L LIGHTWEIGHT M-LOK', 195680, 2, 'ROBINSON', 2950, 'Чохол для транспортування', 'США', 1);
INSERT INTO product VALUES(3, 'ФОРТ 19Р', 32480, 20, 'ФОРТ', 800, 'Пластиковий кейс', 'Україна', 2);
INSERT INTO product VALUES(4, 'SIG SAUER ASP20', 27640, 5, 'Sig Sauer Air', 3500, 'Картонна коробка', 'США', 3);
INSERT INTO product VALUES(5, 'Skif Adventure II BSW', 1520, 10, 'SKIF', 150, 'Коробка', 'Китай', 4);
INSERT INTO product VALUES(6, 'Sellier & Bellot калибр 223 Rem пуля FMJ', 33, 100, 'Sellier & Bellot', 55, 'Картонна коробка', 'Чехія', 5);

#Товар-характеристика-значення
INSERT INTO productvalue VALUES(1, 1, 1, '308Win / 7.62x51 мм');
INSERT INTO productvalue VALUES(2, 1, 2, '508 мм');
INSERT INTO productvalue VALUES(3, 1, 3, '1065 мм');
INSERT INTO productvalue VALUES(4, 1, 4, '22');
INSERT INTO productvalue VALUES(5, 1, 6, 'Пластмаса');
INSERT INTO productvalue VALUES(6, 1, 7, 'Чорний');
INSERT INTO productvalue VALUES(7, 1, 8, 'Нержавіюча сталь');
INSERT INTO productvalue VALUES(8, 1, 9, '5/8 "-24');
INSERT INTO productvalue VALUES(9, 1, 10, '1:11.25"');

INSERT INTO productvalue VALUES(10, 2, 1, '7,62х39');
INSERT INTO productvalue VALUES(11, 2, 2, '375 мм');
INSERT INTO productvalue VALUES(12, 2, 3, '770 мм');
INSERT INTO productvalue VALUES(13, 2, 4, '10');
INSERT INTO productvalue VALUES(14, 2, 6, 'Пластмаса');
INSERT INTO productvalue VALUES(15, 2, 7, 'Зелений');
INSERT INTO productvalue VALUES(16, 2, 8, 'Хромомолібденова сталь');
INSERT INTO productvalue VALUES(17, 2, 9, '5/8 "-24');
INSERT INTO productvalue VALUES(18, 2, 10, '1:10"');

INSERT INTO productvalue VALUES(19, 3, 11, '9 мм Р.А.');
INSERT INTO productvalue VALUES(20, 3, 12, '112 мм');
INSERT INTO productvalue VALUES(21, 3, 13, '208 мм');
INSERT INTO productvalue VALUES(22, 3, 14, '17');
INSERT INTO productvalue VALUES(23, 3, 15, 'Пластмаса');
INSERT INTO productvalue VALUES(24, 3, 18, 'Метал');

INSERT INTO productvalue VALUES(25, 4, 21, '4,5 мм');
INSERT INTO productvalue VALUES(26, 4, 22, '495 мм');
INSERT INTO productvalue VALUES(27, 4, 23, '1158 мм');
INSERT INTO productvalue VALUES(28, 4, 24, '1');
INSERT INTO productvalue VALUES(29, 4, 26, 'Полімер');
INSERT INTO productvalue VALUES(30, 4, 27, 'Чорний');
INSERT INTO productvalue VALUES(31, 4, 28, 'Сталь');

INSERT INTO productvalue VALUES(32, 5, 31, 'Сталь');
INSERT INTO productvalue VALUES(33, 5, 32, '2,8 мм');
INSERT INTO productvalue VALUES(34, 5, 33, '97 мм');
INSERT INTO productvalue VALUES(35, 5, 34, '223 мм');
INSERT INTO productvalue VALUES(36, 5, 35, 'G-10');

INSERT INTO productvalue VALUES(37, 6, 36, '.223 Rem');
INSERT INTO productvalue VALUES(38, 6, 37, '100');
INSERT INTO productvalue VALUES(39, 6, 38, '1822');

INSERT INTO supplier VALUES(1, 'Lockheed Martin', 32855961, '0671234567', 'м. Харків, вул. Сумська, 18/20', '4731185631783138');

INSERT INTO worker VALUES(1, 'Вертухайло Олег Петрович', 1, '0961234567', 'м. Харків', 1, '1980-09-13');

INSERT INTO address VALUES(1, 'м. Київ', 'вул. Магістральна');

INSERT INTO buyer VALUES('3664069397',  'Ремік Кирило Олегович', '0679211167', 'remik@gmail.com', 1);

INSERT INTO sales VALUES(1, '3664069397', 1, '2023-03-11 15:45:21');

insert INTO listproduct VALUES(1, 1, 1, 1);
insert INTO listproduct VALUES(2, 1, 6, 50);