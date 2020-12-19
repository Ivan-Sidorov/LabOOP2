#include "mainwindow.h"
#include "hashtable.h"

#include <QApplication>

using namespace std;

int main(int argc, char *argv[]) {

    // Проверка конструктора по умолчанию
    Hashtable<string> collection;
    assert(collection.size() == 0);

    // Добавление ключа
    collection << "Student 1";
    assert(collection.size() == 1);

    // Добавление существующего ключа
    collection << "Student 1";
    assert(collection.size() == 1);
    assert(collection["Student 1"] == 2);

    // Проверка наличия ключа
    assert(collection.inTable("Student 1") == 1);

    // Проверка []
    assert(collection["Student 1"] == 2);

    // Удаление существующего ключа
    collection.delPlayer("Student 1");
    assert(collection.size() == 0);

    // Удаление отсутствующего ключа
    collection.delPlayer("Student 2");
    assert(collection.size() == 0);

    //Проверка наличия удаленного ключа
    assert(collection.inTable("Student 1") == 0);

    // Сравнение пустой коллекции и конструктора по умолчанию
    Hashtable<string> newCollection;
    assert(collection == newCollection);

    // Проверка конструктора копирования
    Hashtable<string> copyCollection(collection);
    assert(collection == copyCollection);
    // После изменения одной из коллекций
    copyCollection << "Student 1";
    assert(collection != copyCollection);

    //Проверка загрузки из файла и записи в файл
    Hashtable<string> outCollection;
    outCollection << "Student 1";
    outCollection << "Student 2";
    assert(outCollection.toFile("testColl.txt") == 1);
    Hashtable<string> inCollection;
    assert(inCollection.fromFile("testColl.txt") == 1);
    assert(inCollection == outCollection);

    //Проверка удаления всей коллекции
    assert(inCollection.clear() == 1);
    assert(inCollection.size() == 0);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
