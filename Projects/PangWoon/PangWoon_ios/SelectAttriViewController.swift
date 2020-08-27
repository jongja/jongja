//
//  SelectAttriViewController.swift
//  PangWoon
//
//  Created by 종자 on 2018. 8. 9..
//  Copyright © 2018년 Imagic. All rights reserved.
//

import UIKit

class SelectAttriViewController: UIViewController {

    @IBOutlet weak var MultiButton: UIButton!
    @IBOutlet weak var China: UIButton!
    @IBOutlet weak var DosirakButton: UIButton!
    @IBOutlet weak var Season: UIButton!
    @IBOutlet weak var Rice: UIButton!
    @IBOutlet weak var Meat: UIButton!
    @IBOutlet weak var Hand: UIButton!
    @IBOutlet weak var Cuttlet: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let radius: CGFloat = 40.0
        MultiButton.layer.cornerRadius = radius
        MultiButton.layer.masksToBounds = true
        China.layer.cornerRadius = radius
        China.layer.masksToBounds = true
        DosirakButton.layer.cornerRadius = radius
        DosirakButton.layer.masksToBounds = true
        Season.layer.cornerRadius = radius
        Season.layer.masksToBounds = true
        Rice.layer.cornerRadius = radius
        Rice.layer.masksToBounds = true
        Meat.layer.cornerRadius = radius
        Meat.layer.masksToBounds = true
        Hand.layer.cornerRadius = radius
        Hand.layer.masksToBounds = true
        Cuttlet.layer.cornerRadius = radius
        Cuttlet.layer.masksToBounds = true
        
        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func PushBackButton(_ sender: Any) {
        self.navigationController?.popViewController(animated: true)
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        switch segue.identifier {
        case "multi":
            (segue.destination as! NearStoreViewController).stores = list_dict["멀티집"]!
        case "noodle":
            (segue.destination as! NearStoreViewController).stores = list_dict["면or중국집"]!
        case "meat":
            (segue.destination as! NearStoreViewController).stores = list_dict["고기(갈비,삼겹살)"]!
        case "cuttlet":
            (segue.destination as! NearStoreViewController).stores = list_dict["돈까스or분식"]!
        case "rice":
            (segue.destination as! NearStoreViewController).stores = list_dict["국과 밥"]!
        case "hand":
            (segue.destination as! NearStoreViewController).stores = list_dict["들고먹는거"]!
        case "seasonrice":
            (segue.destination as! NearStoreViewController).stores = list_dict["덮밥"]!
        case "dosirak":
            (segue.destination as! NearStoreViewController).stores = list_dict["도시락"]!
        default:
            (segue.destination as! NearStoreViewController).stores = list_dict["멀티집"]!
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
