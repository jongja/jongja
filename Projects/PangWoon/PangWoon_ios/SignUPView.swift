//
//  SignUPView.swift
//  PracticeAPP
//
//  Created by 종자 on 2018. 7. 21..
//  Copyright © 2018년 Jongja. All rights reserved.
//

import UIKit
import Foundation
class SignUPView: UIViewController, UITextFieldDelegate {

    @IBOutlet weak var StudentIDField: UITextField!
    @IBOutlet weak var PasswordField: UITextField!
    
    @IBOutlet weak var AutoLoginButton: UIButton!
    @IBOutlet weak var LoginButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let file = fileIO.init()
        if file.isDirExist(Directory_name: "LoginData") {
            print(file.readFromfile(datapath: file.getDirPath(Directory_name: "LoginData"), filename: "data.txt")!)
            let move = self.storyboard?.instantiateViewController(withIdentifier: "main")
            self.navigationController?.pushViewController(move!, animated: true)
        }
        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?){
        self.view.endEditing(true)
        LoginButton.setTitle("Login", for: UIControlState.normal)
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
    @IBAction func SelectAutoLogin(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
        if sender.isSelected == true {
            sender.setBackgroundImage(UIImage(named: "selectedButton.png"), for: .normal)
        }else{
            sender.setBackgroundImage(UIImage(named: "notselectedButton.png"), for: .normal)
        }
    }
    
    @IBAction func LoginAction(_ sender: Any) {
        let ID = StudentIDField.text!
        let Password = PasswordField.text!
        self.view.endEditing(true)
        
        let tempfile = fileIO.init()
        if tempfile.isDirExist(Directory_name: "LoginData"){
            tempfile.deleteDir(Directory_name: "LoginData")
        }
        
        let res = connect(query: "login/\(ID)/\(Password)")
        if res == nil {
            let alert = UIAlertController(title: "알림", message: "서버에 접속 할 수 없습니다.", preferredStyle: UIAlertControllerStyle.alert)
            let ok = UIAlertAction(title: "확인", style: UIAlertActionStyle.default, handler: nil)
            alert.addAction(ok)
            present(alert, animated: true, completion: nil)
        }else if res! == "NotAccess\n"{
            let alert = UIAlertController(title: "알림", message: "비밀번호가 틀렸습니다.", preferredStyle: UIAlertControllerStyle.alert)
            let ok = UIAlertAction(title: "확인", style: UIAlertActionStyle.default, handler: nil)
            alert.addAction(ok)
            present(alert, animated: true, completion: nil)
        }else if res! == "NoData\n"{
            let alert = UIAlertController(title: "알림", message: "계정이 존재하지 않습니다.", preferredStyle: UIAlertControllerStyle.alert)
            let ok = UIAlertAction(title: "확인", style: UIAlertActionStyle.default, handler: nil)
            alert.addAction(ok)
            present(alert, animated: true, completion: nil)
        }else{
            let resarr = res!.split(separator: "/").map(String.init)
            if AutoLoginButton.isSelected {
                let file = fileIO.init()
                let dp = file.createDir(Directory_name: "LoginData")
                file.writeTofile(datapath: dp, filename: "data.txt", inputData: "\(ID)/\(Password)/\(resarr[3])/\(resarr[4])/1")
            }else{
                let file = fileIO.init()
                let dp = file.createDir(Directory_name: "LoginData")
                file.writeTofile(datapath: dp, filename: "data.txt", inputData: "\(ID)/\(Password)/\(resarr[3])/\(resarr[4])/0")
            }
            let move = self.storyboard?.instantiateViewController(withIdentifier: "main")
            self.navigationController?.pushViewController(move!, animated: true)
        }
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
