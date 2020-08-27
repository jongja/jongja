//
//  ViewPasswordController.swift
//  PangWoon
//
//  Created by 종자 on 2018. 8. 9..
//  Copyright © 2018년 Imagic. All rights reserved.
//

import UIKit

class ViewPasswordController: UIViewController {

    @IBOutlet weak var Your: UILabel!
    @IBOutlet weak var Pass: UILabel!
    @IBOutlet weak var word: UILabel!
    
    var your = ""
    var password = ""
    var iss = ""
    
    override func viewDidLoad() {
        super.viewDidLoad()
        Pass.text = password
        Your.text = your
        word.text = iss
        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func PushGoToHome(_ sender: Any) {
        let move = self.storyboard?.instantiateViewController(withIdentifier: "root")
        self.navigationController?.pushViewController(move!, animated: true)
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
