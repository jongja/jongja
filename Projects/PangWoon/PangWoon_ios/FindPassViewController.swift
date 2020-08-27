//
//  FindPassViewController.swift
//  PangWoon
//
//  Created by 종자 on 2018. 8. 9..
//  Copyright © 2018년 Imagic. All rights reserved.
//

import UIKit

class FindPassViewController: UIViewController, UIPickerViewDataSource, UIPickerViewDelegate {


    var gender = [""]
    var age = [""]
    
    @IBOutlet weak var studentID: UITextField!
    @IBOutlet weak var AgeText: UIButton!
    @IBOutlet weak var GenderText: UIButton!
    
    @IBOutlet weak var GenderPick: UIPickerView!
    @IBOutlet weak var AgePick: UIPickerView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        GenderPick.isHidden = true
        AgePick.isHidden = true
        gender = ["남", "여"]
        age = ["20","21","22","23","24","25","26","27","28","29","30살이상"]
        // Do any additional setup after loading the view.
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
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
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

    @IBAction func PushBackButton(_ sender: Any) {
        self.navigationController?.popViewController(animated: true)
    }
    
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        let ID = studentID.text!
        let age = AgeText.titleLabel?.text
        let gender = GenderText.titleLabel?.text
        
        print(ID,age!,gender!)
        
//            send to server.
        let res = connect(query: "Findpass/\(ID)/\(gender!)/\(age!)/")
        let splited_res = res?.split(separator: "/").map(String.init)
        
        if segue.identifier == "GoToViewPass" {
            if splited_res![0] == "FindSuccess" {
                (segue.destination as! ViewPasswordController).your = "당신의 비밀번호는"
                (segue.destination as! ViewPasswordController).password = splited_res![1]  //the result will view to next view controller
                (segue.destination as! ViewPasswordController).iss = "입니다."
            }
            else{
                (segue.destination as! ViewPasswordController).your = "입력 정보를"
                (segue.destination as! ViewPasswordController).password = "확인해"
                (segue.destination as! ViewPasswordController).iss = "주세요"
            }
            
        }
        
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
