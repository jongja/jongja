//
//  ViewController.swift
//  SignUpForm
//
//  Created by 종자 on 2018. 7. 12..
//  Copyright © 2018년 Jongja. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITextFieldDelegate {

    @IBOutlet weak var BlogField: UITextField!
    @IBOutlet weak var TelField: UITextField!
    @IBOutlet weak var PasswordField: UITextField!
    @IBOutlet weak var EmailTextField: UITextField!
    @IBOutlet weak var nameTextField: UITextField!
    @IBOutlet weak var OutputText: UITextView!
    override func viewDidLoad() {
        super.viewDidLoad()
//        nameTextField.delegate = self  //or delegate like
//        EmailTextField.delegate = self
        
        // Do any additional setup after loading the view, typically from a nib.
    }

    @IBAction func SignUpAction(_ sender: Any) {
        self.performSegue(withIdentifier: "secondPage", sender: self)
        
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?){
        self.view.endEditing(true)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

