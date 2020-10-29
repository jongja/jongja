//
//  ViewController.swift
//  XMLParser
//
//  Created by 종자 on 2018. 7. 23..
//  Copyright © 2018년 Jongja. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITableViewDataSource, XMLParserDelegate {

    var datalist = [[String:String]]()
    var detaildata = [String:String]()
    var elementTemp : String = ""
    var blank : Bool = false
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let urlString = "https://raw.githubusercontent.com/ChoiJinYoung/iphonewithswift2/master/weather.xml"
        
        guard let baseURL = URL(string: urlString) else {
            print("URL error")
            return
        }
        guard let parser = XMLParser(contentsOf: baseURL) else{
            print("can't read data")
            return
        }
        parser.delegate = self
        if !parser.parse(){
            print("parse error")
        }
        
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    func parser(_ parser: XMLParser, didStartElement elementName: String, namespaceURI: String?, qualifiedName qName: String?, attributes attributeDict: [String : String] = [:]) {
        elementTemp = elementName
        blank = true
    }
    func parser(_ parser: XMLParser, foundCharacters string: String) {
        if blank && elementTemp != "local" && elementTemp != "weatherinfo" {
            detaildata[elementTemp] = string.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines) //delete no space or anything
        }
    }
    
    func parser(_ parser: XMLParser, didEndElement elementName: String, namespaceURI: String?, qualifiedName qName: String?) {
        if elementName == "local" {
            datalist += [detaildata]
        }
        blank = false
        
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return datalist.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "Cell", for: indexPath) as! TableViewCell
        
        var dicTemp = datalist[indexPath.row]
        cell.NameLabel.text = dicTemp["country"]
        cell.WeatherLabel.text = dicTemp["weather"]
        cell.TempLabel.text  = dicTemp["temperature"]
        switch dicTemp["weather"] {
        case "맑음":
            cell.ImageView.image = UIImage(named: "sunny.png")
        case "흐림":
            cell.ImageView.image = UIImage(named: "cloudy.png")
        case "비":
            cell.ImageView.image = UIImage(named: "rainy.png")
        case "눈":
            cell.ImageView.image = UIImage(named: "snow.png")
        case "우박":
            cell.ImageView.image = UIImage(named: "blizzard.png")
        default:
            cell.ImageView.image = UIImage(named: "sunny.png")
        }
        return cell
    }


    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    


}

