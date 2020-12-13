//
//  ViewController.swift
//  VisualBookManager
//
//  Created by 종자 on 2018. 7. 10..
//  Copyright © 2018년 Imagic_Jongja. All rights reserved.
//

import UIKit

struct Book{
    var name: String?
    var genre: String?
    var author: String? //optional value.
}

class ViewController: UIViewController {
    
    var myBookManager = BookManager()
    
    @IBOutlet weak var OutputTextView: UITextView!
    
    @IBOutlet weak var NameField: UITextField!
    @IBOutlet weak var AuthorField: UITextField!
    @IBOutlet weak var GenreField: UITextField!
    @IBOutlet weak var countLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        let book1 = Book(name: "햄릿", genre: "비극", author:"셰익스피어")
        let book2 = Book(name: "어린왕자", genre: "소설", author:"쌩떽쥐페리")
        let book3 = Book(name: "죄와벌", genre: "사실주의", author:"톨스토이")
        
        myBookManager.registerBook(Insert_Book_Struct: book1)
        myBookManager.registerBook(Insert_Book_Struct: book2)
        myBookManager.registerBook(Insert_Book_Struct: book3)
        countLabel.text = " \(myBookManager.countBooks())"
    }
    
    @IBAction func showAllBookAction( _ sender: Any){
        OutputTextView.text = myBookManager.showAllBooks()
    }
    
    @IBAction func registerAction( _ sender: Any) {
        var bookTemp = Book()
        if (NameField.text != "") && (AuthorField.text != "") && (GenreField.text != "") {
            bookTemp.name = NameField.text!
            bookTemp.author = AuthorField.text!
            bookTemp.genre = GenreField.text!
            myBookManager.registerBook(Insert_Book_Struct: bookTemp)
            OutputTextView.text = "\n\n\t\t\t\(bookTemp.name!) is registered."
            countLabel.text = " \(myBookManager.countBooks())"
        }
        clearTextField()
    }
    @IBAction func searchAction( _ sender : Any) {
        let resultBook = myBookManager.searchBooks(name: NameField.text!)
        if resultBook == nil {
            OutputTextView.text = "\n\n\t\t\tCan't find \(NameField.text!)."
        }else{
            OutputTextView.text = "\(resultBook!)"
        }
        clearTextField()
    }
    
    @IBAction func deleteAction( _ sender : Any) {
        let deleted = myBookManager.removeBook(name: NameField.text!)
        if deleted {
            OutputTextView.text = "\n\n\t\t\t\(NameField.text!) is deleted."
            countLabel.text = " \(myBookManager.countBooks())"
        }else
        {
            OutputTextView.text = "\n\n\t\t\tDelete failed."
        }
        clearTextField()
    }
    
    func clearTextField(){
        NameField.text = nil
        AuthorField.text = nil
        GenreField.text = nil
    }
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?){
        self.view.endEditing(true)
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

