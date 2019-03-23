using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace ConsoleApp3
{
    class Program
    {
        static void Main(string[] args)
        {
            Pusk();
        }
        static void Pusk()
        {
            string message;
            Console.WriteLine("1 - Добавить \n2 - Показать\nВаш Ответ:");
            message = Console.ReadLine();
            if (message == "1" || message == "2")
            {
                if (message == "1")
                {
                    string name;
                    Console.Clear();
                    Console.WriteLine("Добавить в какую категорию?\n1 - Не взял трубку\n2 - Взял трубку\n3 - Отказался\n4 - Неопределился\n5 - Согласился на встречу\n");
                    name = Console.ReadLine();
                    if (name != "1" || name != "2" || name != "3" || name != "4" || name != "5")
                    {
                        switch (name)
                        {
                            case "1":
                                string mess;
                                Console.WriteLine("Введите сообщение:");
                                mess=Console.ReadLine();
                                FileStream file = new FileStream("C:\\Users\\1\\Desktop\\прога компания\\Не взял трубку.txt", FileMode.Append); //открытие файла на дозапись в конец файла
                                StreamWriter writer = new StreamWriter(file); //создаем «потоковый писатель» и связываем его с файловым потоком 
                                writer.WriteLine(mess); //записываем в файл
                                writer.Close(); //закрываем поток. Не закрыв поток, в файл ничего не запишется 
                                break;
                            case "2":
                                string mess1;
                                Console.WriteLine("Введите сообщение:");
                                mess1 = Console.ReadLine();
                                FileStream file1 = new FileStream("C:\\Users\\1\\Desktop\\прога компания\\Взял трубку.txt", FileMode.Append); //открытие файла на дозапись в конец файла
                                StreamWriter writer1 = new StreamWriter(file1); //создаем «потоковый писатель» и связываем его с файловым потоком 
                                writer1.WriteLine(mess1); //записываем в файл
                                writer1.Close(); //закрываем поток. Не закрыв поток, в файл ничего не запишется 
                                break;
                            case "3":
                                string mess2;
                                Console.WriteLine("Введите сообщение:");
                                mess = Console.ReadLine();
                                FileStream file2 = new FileStream("C:\\Users\\1\\Desktop\\прога компания\\Отказался.txt", FileMode.Append); //открытие файла на дозапись в конец файла
                                StreamWriter writer2 = new StreamWriter(file2); //создаем «потоковый писатель» и связываем его с файловым потоком 
                                writer2.WriteLine(mess); //записываем в файл
                                writer2.Close(); //закрываем поток. Не закрыв поток, в файл ничего не запишется 
                                break;
                            case "4":
                                string mess3;
                                Console.WriteLine("Введите сообщение:");
                                mess3 = Console.ReadLine();
                                FileStream file3 = new FileStream("C:\\Users\\1\\Desktop\\прога компания\\Неопределился.txt", FileMode.Append); //открытие файла на дозапись в конец файла
                                StreamWriter writer3 = new StreamWriter(file3); //создаем «потоковый писатель» и связываем его с файловым потоком 
                                writer3.WriteLine(mess3); //записываем в файл
                                writer3.Close(); //закрываем поток. Не закрыв поток, в файл ничего не запишется 
                                break;
                            case "5":
                                string mess4;
                                Console.WriteLine("Введите сообщение:");
                                mess = Console.ReadLine();
                                FileStream file4 = new FileStream("C:\\Users\\1\\Desktop\\прога компания\\Согласился на встречу.txt", FileMode.Append); //открытие файла на дозапись в конец файла
                                StreamWriter writer4 = new StreamWriter(file4); //создаем «потоковый писатель» и связываем его с файловым потоком 
                                writer4.WriteLine(mess); //записываем в файл
                                writer4.Close(); //закрываем поток. Не закрыв поток, в файл ничего не запишется 
                                break;
                        }
                        Console.Clear();
                        Pusk();
                    }
                    else
                    {
                        Console.Clear();
                        Console.WriteLine("Введите только цифры от 1 до 5");
                        Pusk();
                    }
                }
                else
                {
                    Console.Clear();
                    Console.WriteLine("Показать какой тип:\n1 - Не взяли трубку\n2 - Взяли трубку\n3 - Отказался\n4 - Неопределился\n5 - Согласился на встречу\n");
                    string mess1;
                    mess1 = Console.ReadLine();
                    switch (mess1)
                    {
                        case "1":
                            FileStream file1 = new FileStream("C:\\Users\\1\\Desktop\\прога компания\\Не взял трубку.txt", FileMode.Open); //создаем файловый поток
                            StreamReader reader = new StreamReader(file1); // создаем «потоковый читатель» и связываем его с файловым потоком 
                            Console.WriteLine(reader.ReadToEnd());
                            //Console.WriteLine(reader.ReadLine()); //считываем все данные с потока и выводим на экран
                            reader.Close(); //закрываем поток
                            Console.ReadLine();
                            break;
                    }
                }
            }
            else
            {
                Console.Clear();
                Pusk();
            }
        }
    }
}
