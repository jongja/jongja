//
//  ViewController.swift
//  SelectCar
//
//  Created by 종자 on 2018. 7. 16..
//  Copyright © 2018년 Jongja. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UIPickerViewDataSource, UIPickerViewDelegate{ //must inherit two protocol(datasource, delegate)
    @IBOutlet weak var ImageView: UIImageView!
    
    let carCompanyName = ["Tesla", "Lamborghini", "Porsche"]
    var carModel = [String]()
    var carModelImage:[String] = []
    
    let tesla = ["Model S", "Model X"]
    let lamborghini = ["aventador", "veneno", "huracan"]
    let porsche = ["911", "boxter"]
    
    let teslaImageNames = [ "tesla-model-s.jpg", "tesla-model-x.jpg"]
    let lamborghiniImageNames = ["lamborghini-aventador.jpg", "lamborghini-veneno.jpg", "lamborghini-huracan.jpg"]
    let porscheImageNames = ["porsche-911.jpg", "porsche-boxter.jpg"]
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        carModelImage = teslaImageNames
        carModel = tesla
        ImageView.layer.cornerRadius = 50.0
        ImageView.layer.masksToBounds = true
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 2
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        if component == 0 {
            return carCompanyName[row]
        }else{
            return carModel[row]
        }
    }
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        if component == 0{
            return carCompanyName.count
        }else{
            return carModel.count
        }
    }
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        if component == 0 && row == 0 {
            carModel = tesla
            carModelImage = teslaImageNames
        }
        else if component == 0 && row == 1 {
            carModel = lamborghini
            carModelImage = lamborghiniImageNames
        }
        else if component == 0 && row == 2{
            carModel = porsche
            carModelImage = porscheImageNames
        }
        pickerView.reloadAllComponents()
      
        ImageView.image = UIImage(named: carModelImage[pickerView.selectedRow(inComponent: 1)])
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

