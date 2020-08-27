//
//  fileIO.swift
//  PracticeAPP
//
//  Created by 종자 on 2018. 7. 23..
//  Copyright © 2018년 Jongja. All rights reserved.
//

import Foundation

class fileIO {
    var fm : FileManager
    init() {
        fm = FileManager()
    }
    
    func createDir(Directory_name dname : String) -> URL{
        let dir = fm.urls(for: .documentDirectory, in: .userDomainMask).first!
        let datapath = dir.appendingPathComponent(dname)
        do {
            try fm.createDirectory(atPath: datapath.path, withIntermediateDirectories: false, attributes: nil)
        }catch let error as NSError {
            print("Error create dir: \(error.localizedDescription)")
        }
        return datapath
    }
    
    func getDirPath(Directory_name dname : String) -> URL {
        let dir = fm.urls(for: .documentDirectory, in: .userDomainMask).first!
        let datapath = dir.appendingPathComponent(dname)
        return datapath
    }
    
    func deleteDir(Directory_name dname : String) {
        let dir = fm.urls(for: .documentDirectory, in: .userDomainMask).first!
        let datapath = dir.appendingPathComponent(dname)
        do {
            try fm.removeItem(at: datapath)
        }catch let error as NSError {
            print("Error delete dir: \(error.localizedDescription)")
        }
    }
    
    func isDirExist(Directory_name dname : String) -> Bool {
        let dir = fm.urls(for: .documentDirectory, in: .userDomainMask).first!
        let datapath = dir.appendingPathComponent(dname)
        return datapath.hasDirectoryPath
    }
    
    func writeTofile(datapath: URL, filename : String, inputData : String){
        do{
            let txtpath = datapath.appendingPathComponent(filename)
            let data = inputData
            do{
                try data.write(to: txtpath, atomically: false, encoding: .utf8)
            }catch let error as NSError {
                print("Error Writing File : \(error.localizedDescription)")
            }
        }
    }

    func readFromfile(datapath: URL, filename: String)-> String? {
        do {
            let readPath = datapath.appendingPathComponent(filename)
            let text = try String(contentsOf: readPath, encoding: .utf8)
            return text
        }catch let error as NSError {
        print("Error Reading File : \(error.localizedDescription)")
        }
        return nil
    }
}
