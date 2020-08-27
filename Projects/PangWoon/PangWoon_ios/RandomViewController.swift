//
//  RandomViewController.swift
//  PangWoon
//
//  Created by 종자 on 2018. 7. 19..
//  Copyright © 2018년 Imagic. All rights reserved.
//

import UIKit

class RandomViewController: UIViewController {

    @IBOutlet weak var StoreRandomRecom: UILabel!
    override func viewDidLoad() {
        super.viewDidLoad()
        let idx = Int(arc4random_uniform(UInt32(StoreDict.count))) + 1
        StoreRandomRecom.text = "\"\(StoreDict[idx]!)\""
        // Do any additional setup after loading the view.
    }

    @IBAction func pushBackButton(_ sender: Any) {
        self.navigationController?.popViewController(animated: true)
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
