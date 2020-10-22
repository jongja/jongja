//
//  ViewController.swift
//  TodayApp
//
//  Created by 종자 on 2018. 9. 19..
//  Copyright © 2018년 Jongja. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var TimeLabel: UILabel!
    @IBOutlet weak var apmLabel: UILabel!
    @IBOutlet weak var HighTemp: UILabel!
    @IBOutlet weak var LowTemp: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let now = Date()
        let formatter = DateFormatter()
        formatter.locale = Locale(identifier:"ko_KR")
        formatter.timeZone = TimeZone(abbreviation: "KST")
        formatter.dateFormat = "hh : mm"
        TimeLabel.text = formatter.string(from: now)
        formatter.dateFormat = "a"
        apmLabel.text = formatter.string(from: now)
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

