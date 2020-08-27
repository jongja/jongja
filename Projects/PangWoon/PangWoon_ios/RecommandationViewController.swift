//
//  RecommandationViewController.swift
//  PangWoon
//
//  Created by 종자 on 2018. 7. 19..
//  Copyright © 2018년 Imagic. All rights reserved.
//

import UIKit

class RecommandationViewController: UIViewController, UIPickerViewDataSource, UIPickerViewDelegate {
    
    @IBOutlet weak var insertPeople: UIButton!
    @IBOutlet weak var insertPrice: UIButton!
    @IBOutlet weak var insertFreq: UIButton!
    
    @IBOutlet weak var selectPeoplePick: UIPickerView!
    @IBOutlet weak var selectPricePick: UIPickerView!
    @IBOutlet weak var selectFreqPick: UIPickerView!
    
    @IBOutlet weak var Bab: UIButton!
    @IBOutlet weak var SeasonedBob: UIButton!
    @IBOutlet weak var Chinese: UIButton!
    @IBOutlet weak var Cuttlet: UIButton!
    @IBOutlet weak var Lightfood: UIButton!
    @IBOutlet weak var fastfood: UIButton!
    @IBOutlet weak var noodles: UIButton!
    
    @IBOutlet weak var Loading: UILabel!
    
    var howMuchPrice = [""]
    var howmanypeople  = [""]
    var howmanyeat = [""]
    var people = 0
    var price = 0
    var freq = 0
    var ID : String = ""
    var gender : String = ""
    var age : Int = 0
    var recomResult : String = ""
    
    override func viewDidLoad() {
        super.viewDidLoad()
        selectPeoplePick.isHidden = true
        selectPricePick.isHidden = true
        selectFreqPick.isHidden = true
        Loading.isHidden = true
        howMuchPrice = ["5000원미만", "5000원 ~ 8000원", "8000원 이상"]
        howmanypeople = ["혼자입니다", "2~4명", "5명이상"]
        howmanyeat = ["처음입니다", "두 끼입니다", "세 끼 이상입니다"]
        // Do any additional setup after loading the view.
    }
    
    @IBAction func pushBackButton(_ sender: Any) {
        self.navigationController?.popViewController(animated: true)
    }

    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        if pickerView.tag == 0 {
            return howmanypeople.count
        }
        else if pickerView.tag == 1{
            return howMuchPrice.count
        }else{
            return howmanyeat.count
        }
    }
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        if pickerView.tag == 0
        {
            return howmanypeople[row]
        }
        else if pickerView.tag == 1{
            return howMuchPrice[row]
        }else{
            return howmanyeat[row]
        }
    }
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        if pickerView.tag == 0{
            insertPeople.setTitle("\(howmanypeople[row])", for: UIControlState.normal)
            insertPeople.setTitleColor(UIColor.black, for: UIControlState.normal)
            people = row
        }else if pickerView.tag == 1{
            insertPrice.setTitle("\(howMuchPrice[row])", for: UIControlState.normal)
            insertPrice.setTitleColor(UIColor.black, for: UIControlState.normal)
            price = row
        }else{
            insertFreq.setTitle("\(howmanyeat[row])", for: UIControlState.normal)
            insertFreq.setTitleColor(UIColor.black, for: UIControlState.normal)
            freq = row
        }
    }
    @IBAction func pushSelectPeopleButton(_ sender: Any) {
        selectPeoplePick.isHidden = false
        selectPricePick.isHidden = true
        selectFreqPick.isHidden = true
        
    }
    @IBAction func pushSelectPriceButton(_ sender: Any) {
        selectPricePick.isHidden = false
        selectPeoplePick.isHidden = true
        selectFreqPick.isHidden = true
    }
    @IBAction func pushSelectFreqButton(_ sender: Any) {
        selectFreqPick.isHidden = false
        selectPricePick.isHidden = true
        selectPeoplePick.isHidden = true
    }
    
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?){
        self.view.endEditing(true)
        selectPeoplePick.isHidden = true
        selectPricePick.isHidden = true
        selectFreqPick.isHidden = true
    }

    @IBAction func checkBoxAction(_ sender: UIButton) {
        selectPeoplePick.isHidden = true
        selectPricePick.isHidden = true
        selectFreqPick.isHidden = true
        sender.isSelected = !sender.isSelected
        if sender.isSelected == true {
            sender.setBackgroundImage(UIImage(named: "selectedButton.png"), for: .normal)
        }else{
            sender.setBackgroundImage(UIImage(named: "notselectedButton.png"), for: .normal)
        }
    }
    @IBAction func TouchRecomButton(_ sender: Any) {
       
    }
    
    func makeArr(gender: String, age: Int) -> Array<Int>{
        var arr : Array<Int> = []
        //gender
        if gender == "남" {
            arr.append(0)
        }else{
            arr.append(1)
        }
        //age
        if age >= 20 && age < 23{
            arr.append(0)
        }else if age >= 23 && age < 26{
            arr.append(1)
        }else if age >= 26 && age < 30{
            arr.append(2)
        }else if age >= 30{
            arr.append(3)
        }
        arr.append(price)
        arr.append(people)
        arr.append(freq)
        arr.append(BooltoInt(inputBooltypeVar: Bab.isSelected))
        arr.append(BooltoInt(inputBooltypeVar: Lightfood.isSelected))
        arr.append(BooltoInt(inputBooltypeVar: Chinese.isSelected))
        arr.append(BooltoInt(inputBooltypeVar: Cuttlet.isSelected))
        arr.append(BooltoInt(inputBooltypeVar: noodles.isSelected))
        arr.append(BooltoInt(inputBooltypeVar: SeasonedBob.isSelected))
        arr.append(BooltoInt(inputBooltypeVar: fastfood.isSelected))
        return arr
    }
    
    func BooltoInt(inputBooltypeVar input: Bool) -> Int{ //change bool to integer function
        if input == true{
            return 1
        }else{
            return 0
        }
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
 
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        var error = false
        let res = makeArr(gender: gender, age: age)
        var sndpkt = "0/\(ID)"
        for i in res {
            sndpkt = "\(sndpkt)/\(i)"
        }
        let recomResult = connect(query: sndpkt)
        if recomResult == nil {
            error = true
        }
        var split_res = [""]
        var split_res_3 = [""]
        if !error{
            split_res = recomResult!.split(separator: "/").map(String.init) //split string by "/"
            split_res_3 = split_res[3].split(separator: "\n").map(String.init)
        }
        if segue.identifier == "GoToRecomResult" {
            if split_res[0] == "RecommendOk"{ //if server send messeage with 'ok'
                (segue.destination as! RecomResultViewController).storename_1 =  Int(split_res[1])!
                (segue.destination as! RecomResultViewController).storename_2 = Int(split_res[2])!
                (segue.destination as! RecomResultViewController).storename_3 = Int(split_res_3[0])!
                (segue.destination as! RecomResultViewController).userid = ID
            }
            else {
                (segue.destination as! RecomResultViewController).storename_1 = -1
                (segue.destination as! RecomResultViewController).storename_2 = -1
                (segue.destination as! RecomResultViewController).storename_3 = -1
            }
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
