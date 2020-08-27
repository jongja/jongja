//
//  LoginViewController.swift
//  PracticeAPP
//
//  Created by 종자 on 2018. 7. 21..
//  Copyright © 2018년 Jongja. All rights reserved.
// This code is Login code

import UIKit

class LoginViewController: UIViewController, UIPickerViewDataSource, UIPickerViewDelegate {

    var gender = [""]
    var age = [""]
    
    @IBOutlet weak var GenderPick: UIPickerView!
    @IBOutlet weak var AgePick: UIPickerView!
    
    @IBOutlet weak var StuIDText: UITextField!
    @IBOutlet weak var PasswordText: UITextField!
    
    @IBOutlet weak var GenderText: UIButton!
    @IBOutlet weak var AgeText: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        GenderPick.isHidden = true
        AgePick.isHidden = true
        gender = ["남", "여"]
        age = ["20","21","22","23","24","25","26","27","28","29","30살이상"]
        let file = fileIO.init()
        if file.isDirExist(Directory_name: "LoginData") {
            file.deleteDir(Directory_name: "LoginData")
        }
        // Do any additional setup after loading the view.
    }
    
    //PickerView required Methods
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        if pickerView.tag == 0{
            return age.count
        }else{
            return gender.count
        }
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        if pickerView.tag == 0 {
            return age[row]
        }else{
            return gender[row]
        }
    }
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        if pickerView.tag == 0 {
            AgeText.setTitle("\(age[row])", for: UIControlState.normal)
            AgeText.setTitleColor(UIColor.black, for: UIControlState.normal)
        }else{
            GenderText.setTitle("\(gender[row])", for: UIControlState.normal)
            GenderText.setTitleColor(UIColor.black, for: UIControlState.normal)
        }
    }
    
    // end of picker view method
    
    @IBAction func EndEditID(_ sender: UITextField) {
        sender.resignFirstResponder()
    }
    
    @IBAction func TouchAgeSection(_ sender: Any) {
        self.view.endEditing(true)
        GenderPick.isHidden = true
        AgePick.isHidden = false
    }

    @IBAction func TouchGenderSection(_ sender: Any) {
        self.view.endEditing(true)
        GenderPick.isHidden = false
        AgePick.isHidden = true
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?){
        self.view.endEditing(true)
        GenderPick.isHidden = true
        AgePick.isHidden = true
    }
    
    @IBAction func TouchBackButton(_ sender: Any) {
        self.navigationController?.popViewController(animated: true)
    }
    
    @IBAction func TouchMemberJoinButton(_ sender: Any) {
        GenderPick.isHidden = true
        AgePick.isHidden = true
        let ID = StuIDText.text!
        let Password = PasswordText.text!
        let Gender = GenderText.titleLabel?.text
        var Age = AgeText.titleLabel?.text
        if Age == "30살이상" {
            Age = "30"
        }
        print(ID,Password,Gender!,Age!)
        let file = fileIO.init()
        let dp = file.createDir(Directory_name: "LoginData")
        file.writeTofile(datapath: dp, filename: "data.txt", inputData: "\(ID)/\(Password)/\(Gender!)/\(Age!)/1")
        _ = connect(query : "Register/\(ID)/\(Password)/\(Gender!)/\(Age!)")
    }

    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
