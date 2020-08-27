//
//  DetailStoreViewController.swift
//  PangWoon
//
//  Created by 종자 on 2018. 7. 19..
//  Copyright © 2018년 Imagic. All rights reserved.
//

import UIKit

class DetailStoreViewController: UIViewController, UITableViewDataSource, UITextFieldDelegate, UIPickerViewDelegate, UIPickerViewDataSource {

    
    
    @IBOutlet weak var StoreNameLabel: UILabel!
    
    @IBOutlet weak var star1: UIImageView!
    @IBOutlet weak var star2: UIImageView!
    @IBOutlet weak var star3: UIImageView!
    @IBOutlet weak var star4: UIImageView!
    @IBOutlet weak var star5: UIImageView!
    
    @IBOutlet weak var WriteReview: UITextField!
    
    @IBOutlet weak var StarButton: UIButton!
    
    @IBOutlet weak var StarScorePick: UIPickerView!
    
    var storeName = ""
    var starscore : Float = 0.0
    var reviews = [""]
    let numbers = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
    var sendStarScore = ""
    
    override func viewDidLoad() {
        super.viewDidLoad()
        if reviews[0] == "error" {
            let alert = UIAlertController(title: "알림", message: "서버에 접속 할 수 없습니다.", preferredStyle: UIAlertControllerStyle.alert)
            let ok = UIAlertAction(title: "확인", style: UIAlertActionStyle.default, handler: {
                (action: UIAlertAction!) in
                self.navigationController?.popViewController(animated: true)
            })
            alert.addAction(ok)
            present(alert, animated: true, completion: nil)
        }
        StarScorePick.isHidden = true
        StoreNameLabel.text = storeName
        star1.image = starscore >= 2 ? #imageLiteral(resourceName: "wholestar") : starscore >= 1 ? #imageLiteral(resourceName: "halfstar") : #imageLiteral(resourceName: "emptystar")
        star2.image = starscore >= 4 ? #imageLiteral(resourceName: "wholestar") : starscore >= 3 ? #imageLiteral(resourceName: "halfstar") : #imageLiteral(resourceName: "emptystar")
        star3.image = starscore >= 6 ? #imageLiteral(resourceName: "wholestar") : starscore >= 5 ? #imageLiteral(resourceName: "halfstar") : #imageLiteral(resourceName: "emptystar")
        star4.image = starscore >= 8 ? #imageLiteral(resourceName: "wholestar") : starscore >= 7 ? #imageLiteral(resourceName: "halfstar") : #imageLiteral(resourceName: "emptystar")
        star5.image = starscore >= 10 ? #imageLiteral(resourceName: "wholestar") : starscore >= 9 ? #imageLiteral(resourceName: "halfstar") : #imageLiteral(resourceName: "emptystar")
        NotificationCenter.default.addObserver(self, selector: #selector(keyboardWillShow(_:)), name: .UIKeyboardWillShow, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(keyboardWillHide(_:)), name: .UIKeyboardWillHide, object: nil)
        
        // Do any additional setup after loading the view.
    }

    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
    @objc func keyboardWillShow(_ sender: Notification) {
        self.view.frame.origin.y = -270 // Move view 270 points upward
    }
    @objc func keyboardWillHide(_ sender: Notification) {
        self.view.frame.origin.y = 0 // Move view to original position
    }
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?){
        self.view.endEditing(true)
        StarScorePick.isHidden = true
    }
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return reviews.count-1
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "reviewcell", for: indexPath) as! MyCells2
        let arg = reviews[indexPath.row].components(separatedBy: "->")
        
        let halfarg = arg[0].components(separatedBy: " - ")
        cell.review.text = halfarg[1]
        cell.DateLabel.text = halfarg[0]
    
        cell.cellstar1.image = Float(arg[1])! >= 2 ? #imageLiteral(resourceName: "wholestar") : Float(arg[1])! >= 1 ? #imageLiteral(resourceName: "halfstar") : #imageLiteral(resourceName: "emptystar")
        cell.cellstar2.image = Float(arg[1])! >= 4 ? #imageLiteral(resourceName: "wholestar") : Float(arg[1])! >= 3 ? #imageLiteral(resourceName: "halfstar") : #imageLiteral(resourceName: "emptystar")
        cell.cellstar3.image = Float(arg[1])! >= 6 ? #imageLiteral(resourceName: "wholestar") : Float(arg[1])! >= 5 ? #imageLiteral(resourceName: "halfstar") : #imageLiteral(resourceName: "emptystar")
        cell.cellstar4.image = Float(arg[1])! >= 8 ? #imageLiteral(resourceName: "wholestar") : Float(arg[1])! >= 7 ? #imageLiteral(resourceName: "halfstar") : #imageLiteral(resourceName: "emptystar")
        cell.cellstar5.image = Float(arg[1])! >= 10 ? #imageLiteral(resourceName: "wholestar") : Float(arg[1])! >= 9 ? #imageLiteral(resourceName: "halfstar") : #imageLiteral(resourceName: "emptystar")
        
        return cell
    }
    
    @IBAction func pushBackButton(_ sender: Any) {
        self.navigationController?.popViewController(animated: true)
    }
    
    
    @IBAction func PushStarButton(_ sender: Any) {
        StarScorePick.isHidden = false
    }
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return numbers.count
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return numbers[row]
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        StarButton.setTitle( numbers[row], for: UIControlState.normal)
        StarButton.setTitleColor(UIColor.black, for: UIControlState.normal)
        sendStarScore = numbers[row]
    }
    
    @IBAction func PushReviewButton(_ sender: Any) {
        StarScorePick.isHidden = true
        
        if StarButton.currentTitle! == "별점"{
            let alert = UIAlertController(title: "알림", message: "별점을 남겨주세요.", preferredStyle: UIAlertControllerStyle.alert)
            let ok = UIAlertAction(title: "확인", style: UIAlertActionStyle.default, handler: nil)
            alert.addAction(ok)
            present(alert, animated: true, completion: nil)
        }
        else if WriteReview.text! == "" {
            let alert = UIAlertController(title: "알림", message: "후기를 남겨주세요.", preferredStyle: UIAlertControllerStyle.alert)
            let ok = UIAlertAction(title: "확인", style: UIAlertActionStyle.default, handler: nil)
            alert.addAction(ok)
            present(alert, animated: true, completion: nil)
        }else{
            self.view.endEditing(true)
            let now = Date()
            let formatter = DateFormatter()
            formatter.locale = Locale(identifier:"ko_KR")
            formatter.timeZone = TimeZone(abbreviation: "KST")
            formatter.dateFormat = "yyyy.MM.dd HH:mm:ss"
            let today = formatter.string(from: now)
            let res = connect(query: "Sndreview/" + storeName + "/" + sendStarScore + "/" + today + " - " + WriteReview.text!)         //Sndreview/작은집/10/2018.8.11 - 와 역시 작은집 캐굳
            let split_res = res?.split(separator: "/").map(String.init)
            if split_res![0] == "ReviewWriteOk" {
                let alert = UIAlertController(title: "알림", message: "후기가 등록되었어요!", preferredStyle: UIAlertControllerStyle.alert)
                let ok = UIAlertAction(title: "확인", style: UIAlertActionStyle.default, handler: {
                    (action: UIAlertAction!) in
                    self.navigationController?.popViewController(animated: true)
                })
                alert.addAction(ok)
                present(alert, animated: true, completion: nil)
            }
            else{
                let alert = UIAlertController(title: "오류", message: "다시 시도해 주세요.", preferredStyle: UIAlertControllerStyle.alert)
                let ok = UIAlertAction(title: "확인", style: UIAlertActionStyle.default, handler: nil)
                alert.addAction(ok)
                present(alert, animated: true, completion: nil)
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
