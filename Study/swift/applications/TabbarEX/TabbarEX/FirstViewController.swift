//
//  FirstViewController.swift
//  TabbarEX
//
//  Created by 종자 on 2018. 7. 18..
//  Copyright © 2018년 Jongja. All rights reserved.
//

import UIKit

class FirstViewController: UIViewController {

    @IBOutlet weak var FristLabel: UILabel!
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func buttonAction(_ sender: Any) {
        FristLabel.text = "     1번 버튼이 눌렸습니다."
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
