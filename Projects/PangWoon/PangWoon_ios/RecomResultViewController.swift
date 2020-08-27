//
//  RecomResultViewController.swift
//  PangWoon
//
//  Created by 종자 on 2018. 7. 25..
//  Copyright © 2018년 Imagic. All rights reserved.
//

import UIKit

class RecomResultViewController: UIViewController {

    @IBOutlet weak var store1: UILabel!
    @IBOutlet weak var store2: UILabel!
    @IBOutlet weak var store3: UILabel!
    
    var userid = ""
    var storename_1: Int = 0
    var storename_2: Int = 0
    var storename_3: Int = 0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        if storename_1 == -1 {
            let alert = UIAlertController(title: "알림", message: "서버에 접속 할 수 없습니다.", preferredStyle: UIAlertControllerStyle.alert)
            let ok = UIAlertAction(title: "확인", style: UIAlertActionStyle.default, handler: {
                (action: UIAlertAction!) in
                self.navigationController?.popViewController(animated: true)
            })
            alert.addAction(ok)
            present(alert, animated: true, completion: nil)
        }
        if storename_1 >= 0{
            store1.text = StoreDict[storename_1]
            store2.text = StoreDict[storename_2]
            store3.text = StoreDict[storename_3]
        }
        else {
            store1.text = "Error"
            store2.text = "Error"
            store3.text = "Error"
        }
        // Do any additional setup after loading the view.
    }
    @IBAction func PushRerecomButton(_ sender: Any) {
        let alert = UIAlertController(title: "알림", message: "다시 추천 받을래요?", preferredStyle: UIAlertControllerStyle.alert)
        let ok = UIAlertAction(title: "확인", style: UIAlertActionStyle.default, handler: {
            (action: UIAlertAction!) in
            let res = connect(query: "Rerecom/\(self.userid)/\(self.storename_1)/\(self.storename_2)/\(self.storename_3)/")
            if res == nil{
                let alert2 = UIAlertController(title: "알림", message: "서버가 응답하지 않습니다.", preferredStyle: UIAlertControllerStyle.alert)
                let ok = UIAlertAction(title: "확인", style: UIAlertActionStyle.default, handler: {
                    (action: UIAlertAction!) in
                    self.navigationController?.popViewController(animated: true)
                })
                alert2.addAction(ok)
                self.present(alert2, animated: true, completion: nil)
            }
            else{
                var split_res = res?.split(separator: "/").map(String.init)
                if split_res![0] == "RerecomOk" {
                    self.storename_1 = Int(split_res![1])!
                    self.storename_2 = Int(split_res![2])!
                    self.storename_3 = Int(split_res![3])!
                    self.viewDidLoad()
                }
            }
        })
        let no = UIAlertAction(title: "취소", style: UIAlertActionStyle.default, handler: nil)
        alert.addAction(no)
        alert.addAction(ok)
        present(alert, animated: true, completion: nil)
    }
    
    
    @IBAction func PushBackButton(_ sender: Any) {
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
