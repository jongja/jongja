//
//  ViewController.swift
//  FlightBooking
//
//  Created by 종자 on 2018. 7. 14..
//  Copyright © 2018년 Jongja. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var SelectDepartDay: UIButton!
    @IBOutlet weak var SelectReturnDay: UIButton!
    @IBOutlet weak var ReturnDateLabel: UILabel!
    @IBOutlet weak var SelectDate: UIDatePicker!
    var Button : Int = 1
    override func viewDidLoad() {
        super.viewDidLoad()
        SelectDate.isHidden = true
        ReturnDateLabel.isHidden = true
        SelectReturnDay.isHidden = true
        // Do any additional setup after loading the view, typically from a nib.
    }
    @IBAction func ShowDateLookUp(_ sender: UIButton) {
        if !SelectDate.isHidden {
        SelectDate.isHidden = true
    }else{
        SelectDate.isHidden = false
        }
        Button = sender.tag
    }
    
    @IBAction func ShowReturnDateAction(_ sender: UISwitch) {
        SelectReturnDay.isHidden = !sender.isOn
        ReturnDateLabel.isHidden = !sender.isOn
    }
    
    @IBAction func SelectedDateAction(_ sender: UIDatePicker) {
        let formatter = DateFormatter()
        formatter.dateFormat = "YYYY년 M월 d일"
        let strDate = formatter.string(from: sender.date)
        if Button == 1{
            SelectDepartDay.setTitle(strDate, for: UIControlState.normal)
        }else{
            SelectReturnDay.setTitle(strDate, for: UIControlState.normal)
        }
    }
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.view.endEditing(true)
        SelectDate.isHidden = true
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    

}

