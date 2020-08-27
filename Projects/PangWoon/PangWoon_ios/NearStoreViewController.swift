//
//  NearStoreViewController.swift
//  PangWoon
//
//  Created by 종자 on 2018. 7. 19..
//  Copyright © 2018년 Imagic. All rights reserved.
//

import UIKit

class NearStoreViewController: UIViewController, UITableViewDataSource{
    var stores = [""]
    @IBOutlet weak var TableView: UITableView!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    @IBAction func pushBackButton(_ sender: Any) {
        self.navigationController?.popViewController(animated: true)
    }
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return stores.count
    }
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "Cell", for: indexPath) as! MyCells
        cell.storeNameLabel.text = stores[indexPath.row]
        return cell
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        let name = stores[TableView.indexPathForSelectedRow!.row]
        var tempres = [""]
        var splitres = [""]
        var star : Float = 0
        
        var error = false
        let res = connect(query: "Review/\(name)")
        if res == nil{
            error = true
        }
        if !error{
            tempres = res!.split(separator: "/").map(String.init)
            splitres = tempres[1].split(separator: "|").map(String.init)
            star = Float(splitres[0])!
            splitres.remove(at: 0)
        }else{
            splitres[0] = "error"
        }
        
        if segue.identifier == "DetailStore" {
            (segue.destination as! DetailStoreViewController).storeName = name
            (segue.destination as! DetailStoreViewController).reviews = splitres
            (segue.destination as! DetailStoreViewController).starscore = star
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
