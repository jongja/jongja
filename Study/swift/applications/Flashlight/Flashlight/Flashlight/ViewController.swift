//
//  ViewController.swift
//  Flashlight
//
//  Created by 종자 on 2018. 7. 3..
//  Copyright © 2018년 종자. All rights reserved.
//

import UIKit
import AVFoundation //for play sound

class ViewController: UIViewController {

    @IBOutlet weak var SwitchButton: UIButton!
    @IBOutlet weak var flashimageView: UIImageView!

    var isOn = false
    var chicksound: AVAudioPlayer?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        prepareSound() //prepare on constructor
    }

    func prepareSound(){ //sound play function
        let path = Bundle.main.path(forResource: "switch.wav", ofType:nil)! //input file.
        let url = URL(fileURLWithPath: path)
        
        do {
            chicksound = try AVAudioPlayer(contentsOf: url)
            chicksound?.prepareToPlay()
        }
        catch {
            // couldn't load file :(
        }
        
    }
    
    func toggleTorch(on: Bool) { //turn on/off flash light
        guard let device = AVCaptureDevice.default(for: .video) else { return }
        
        if device.hasTorch {
            do {
                try device.lockForConfiguration()
                
                if on == true {
                    device.torchMode = .on
                } else {
                    device.torchMode = .off
                }
                
                device.unlockForConfiguration()
            } catch {
                print("Torch could not be used")
            }
        } else {
            print("Torch is not available")
        }
    }
    
    @IBAction func switchTapped(_ sender: Any) {
        toggleTorch(on: !isOn)
        chicksound?.play()
        isOn = !isOn
        //same function under implement.
//        if isOn == true {
//        SwitchButton.setImage(UIImage(named: "onSwitch"), for: .normal)
//        flashimageView.image = UIImage(named: "onBG")
//        }
//        else {
//            SwitchButton.setImage(UIImage(named: "offSwitch"), for: .normal)
//            flashimageView.image = UIImage(named: "offBG")
//        }
//    }

        flashimageView.image = isOn ? #imageLiteral(resourceName: "onBG") : #imageLiteral(resourceName: "offBG") //same function
        SwitchButton.setImage(isOn ? #imageLiteral(resourceName: "onSwitch") : #imageLiteral(resourceName: "offSwitch"), for: .normal)
    }
}

