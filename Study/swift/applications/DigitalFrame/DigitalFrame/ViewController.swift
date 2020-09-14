//
//  ViewController.swift
//  DigitalFrame
//
//  Created by 종자 on 2018. 7. 11..
//  Copyright © 2018년 Jongja. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var ImgView: UIImageView!
    @IBOutlet weak var toggleButton: UIButton!
    @IBOutlet weak var speedSlider: UISlider!
    @IBOutlet weak var valueSlider: UILabel!
    override func viewDidLoad() {
        super.viewDidLoad()
        let Images = [UIImage.init(named: "1.jpg")!,
                      UIImage.init(named: "2.jpg")!,
                      UIImage.init(named: "3.jpg")!,
                      UIImage.init(named: "4.jpg")!,
                      UIImage.init(named: "5.jpg")!,
                      UIImage.init(named: "6.jpg")!,
                      UIImage.init(named: "7.jpg")!,
                      UIImage.init(named: "8.jpg")!,
                      UIImage.init(named: "9.jpg")!,
                      UIImage.init(named: "10.jpg")!,
                      UIImage.init(named: "11.jpg")!,
                      UIImage.init(named: "12.jpg")!,
                      UIImage.init(named: "13.jpg")!,
                      UIImage.init(named: "14.jpg")!,
                      UIImage.init(named: "15.jpg")!
        ]
        ImgView.animationImages = Images
        valueSlider.text = String(format: " %.2f", speedSlider.value)
        // Do any additional setup after loading the view, typically from a nib.
    }
    @IBAction func setSpeedUsingSlider( _ sender: Any) {
        ImgView.animationDuration = Double(speedSlider.value)
        valueSlider.text = String(format: "%.2f", speedSlider.value)
        if !ImgView.isAnimating {
            ImgView.startAnimating()
            toggleButton.setTitle("Stop", for: UIControlState.normal)
        }
        
    }
    @IBAction func toggleButton( _ sender : Any) {
        if ImgView.isAnimating {
            ImgView.stopAnimating()
            toggleButton.setTitle("Start", for: UIControlState.normal)
        }
        else{
            ImgView.startAnimating()
            ImgView.animationDuration = Double(speedSlider.value)
            toggleButton.setTitle("Stop", for: UIControlState.normal)
        }
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

