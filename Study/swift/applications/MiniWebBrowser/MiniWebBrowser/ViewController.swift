//
//  ViewController.swift
//  MiniWebBrowser
//
//  Created by 종자 on 2018. 7. 13..
//  Copyright © 2018년 Jongja. All rights reserved.
//

import UIKit
import WebKit
class ViewController: UIViewController, UITextFieldDelegate, WKNavigationDelegate {

    @IBOutlet weak var bookMarkSegmentedControl: UISegmentedControl!
    @IBOutlet weak var urlTextField: UITextField!
    @IBOutlet weak var mainWebView: WKWebView!
    @IBOutlet weak var indicateActivity: UIActivityIndicatorView!
    override func viewDidLoad() {
        super.viewDidLoad()
        let firstURL = URL(string: "https://www.apple.com")
        let Req = URLRequest(url: firstURL!)
        mainWebView.load(Req)
        mainWebView.navigationDelegate = self
        urlTextField.text = "https://www.apple.com"
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    func webView(_ webView: WKWebView, didStartProvisionalNavigation navigation: WKNavigation!) {
        indicateActivity.startAnimating()
    }
    func webView(_ webView: WKWebView, didFinish navigation: WKNavigation!) {
        indicateActivity.stopAnimating()
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        var url = "\(urlTextField.text!)"
        if !url.hasPrefix("https://") {
            url = "https://\(urlTextField.text!)"
        }
        urlTextField.text = url
        mainWebView.load(URLRequest(url: URL(string: url)!))
        urlTextField.text = mainWebView.url?.absoluteString
        textField.resignFirstResponder()
        return true
    }

    @IBAction func BookMarkAction(_ sender: Any) {
        let segnum = bookMarkSegmentedControl.selectedSegmentIndex
        let segment = bookMarkSegmentedControl.titleForSegment(at: segnum)
        let changeURL = "https://www.\(segment!).com"
        mainWebView.load(URLRequest(url: URL(string: changeURL)!))
        urlTextField.text = "https://www.\(segment!).com"
    }
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?){
        self.view.endEditing(true)
    }
    @IBAction func GoBackAction(_ sender: Any) {
        urlTextField.text = mainWebView.url?.absoluteString
        mainWebView.goBack()
    }
    @IBAction func GoForwardAction(_ sender: Any) {
        urlTextField.text = mainWebView.url?.absoluteString
        mainWebView.goForward()
    }
    @IBAction func StopAction(_ sender: Any) {
        mainWebView.stopLoading()
    }
    @IBAction func RefreshAction(_ sender: Any) {
        mainWebView.reload()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

