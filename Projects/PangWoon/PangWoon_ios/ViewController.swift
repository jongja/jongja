//
//  ViewController.swift
//  PangWoon
//
//  Created by 종자 on 2018. 7. 14..
//  Copyright © 2018년 Imagic. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    var infoArr = [""]
    @IBOutlet weak var logoutButton: UIButton!
    @IBOutlet weak var UserName: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let file = fileIO.init()
        let dp = file.getDirPath(Directory_name: "LoginData")
        infoArr = file.readFromfile(datapath: dp, filename: "data.txt")!.split(separator: "/").map(String.init)
        UserName.text = "\(infoArr[0])"
        print(infoArr)
        if infoArr[4] == "0" {
            file.deleteDir(Directory_name: "LoginData")
        }
        // Do any additional setup after loading the view, typically from a nib.
    }
  
    @IBAction func pushLogout(_ sender: Any) {
        let alert = UIAlertController(title: "Logout", message: "로그아웃 하실래요?", preferredStyle: UIAlertControllerStyle.alert)
        let ok = UIAlertAction(title: "네", style: UIAlertActionStyle.default, handler: {
            (action: UIAlertAction!) in
            let file = fileIO.init()
            file.deleteDir(Directory_name: "LoginData")
            self.navigationController?.popViewController(animated: true)
        })
        let no = UIAlertAction(title: "아니오", style: UIAlertActionStyle.destructive, handler: nil)
        alert.addAction(ok)
        alert.addAction(no)
        present(alert, animated: true, completion: nil)
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "GoToRecom" {
            (segue.destination as! RecommandationViewController).ID = infoArr[0]
            (segue.destination as! RecommandationViewController).gender = infoArr[2]
            let temp = infoArr[3].split(separator: "\n").map(String.init)
            (segue.destination as! RecommandationViewController).age = Int(temp[0])!
        }
    }
}

