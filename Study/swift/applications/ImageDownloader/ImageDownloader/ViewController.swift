//
//  ViewController.swift
//  ImageDownloader
//
//  Created by 종자 on 2018. 9. 4..
//  Copyright © 2018년 Jongja. All rights reserved.
//

import UIKit

class ViewController: UIViewController, URLSessionDownloadDelegate {
    

    @IBOutlet weak var ImageView: UIImageView!
    @IBOutlet weak var IndicateView: UIActivityIndicatorView!
    @IBOutlet weak var ProgressView: UIProgressView!
    
    var downloadTask : URLSessionDownloadTask!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    
    @IBAction func PushDownloadButton(_ sender: Any) {
        ImageView.image = nil
        IndicateView.startAnimating()
        let sessionConfiguration = URLSessionConfiguration.default
        let session = URLSession(configuration: sessionConfiguration, delegate: self, delegateQueue: OperationQueue.main)
        downloadTask = session.downloadTask(with: URL(string: "https://raw.githubusercontent.com/ChoiJinYoung/iphonewithswift2/master/sample.jpeg")!)
        downloadTask.resume()
    }
    
    @IBAction func PushSuspendButton(_ sender: Any) {
        downloadTask.suspend()
    }
    
    @IBAction func PushResumeButton(_ sender: Any) {
        downloadTask.resume()
    }
    
    @IBAction func PushStopButton(_ sender: Any) {
        downloadTask.cancel()
        IndicateView.stopAnimating()
        ProgressView.setProgress(0, animated: false)
    }
    
    func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask, didFinishDownloadingTo location: URL) {
        let datatemp : Data = try! Data(contentsOf: location)
        self.ImageView.image = UIImage(data: datatemp)
    }
    
    func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask, didWriteData bytesWritten: Int64, totalBytesWritten: Int64, totalBytesExpectedToWrite: Int64) {
        let progress : Float = Float(totalBytesWritten)/Float(totalBytesExpectedToWrite)
        self.ProgressView.setProgress(progress, animated: true)
        if totalBytesExpectedToWrite == totalBytesWritten{
            IndicateView.stopAnimating()
            self.ProgressView.setProgress(0, animated: false)
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

