//
//  BookManager.swift
//  BookManager
//
//  Created by 종자 on 2018. 7. 9..
//  Copyright © 2018년 Imagic_jongja. All rights reserved.
//

class BookManager{
    var booklist = [Book]() //Declare Book type array
    
    func registerBook(Insert_Book_Struct bookObject:Book){
        booklist += [bookObject]
    }
    
    func showAllBooks() -> String {
        var strTemp = ""
        for bookTemp in booklist {
            strTemp += "  \t\tName : \(bookTemp.name!)\n"
            strTemp += "  \t\tGenre : \(bookTemp.genre!)\n"
            strTemp += "  \t\tAuthor : \(bookTemp.author!)\n"
            strTemp += "  \t\t-------------------\n"
        }
        return strTemp
    }

    func countBooks() ->Int{
        return booklist.count
    }
    
    func searchBooks(name:String) -> String?{ //if return value srting and nil.
        var strTemp = ""
        for book in booklist {
            if book.name == name{
                strTemp += "Name : \(book.name!)\n"
                strTemp += "Genre : \(book.genre!)\n"
                strTemp += "Author : \(book.author!)\n"
                return strTemp
            }
        }
        return nil
    }
    func removeBook(name: String) -> Bool{
        for (index, value) in booklist.enumerated() {
            if value.name == name{
                booklist.remove(at: index)
                return true
            }
        }
        return false
    }
    
}
