//
//  MyCells2.swift
//  PangWoon
//
//  Created by 종자 on 2018. 8. 11..
//  Copyright © 2018년 Imagic. All rights reserved.
//

import UIKit

class MyCells2: UITableViewCell {
    
    
    @IBOutlet weak var review: UITextView!
    @IBOutlet weak var cellstar1: UIImageView!
    @IBOutlet weak var cellstar2: UIImageView!
    @IBOutlet weak var cellstar3: UIImageView!
    @IBOutlet weak var cellstar4: UIImageView!
    @IBOutlet weak var cellstar5: UIImageView!
    
    @IBOutlet weak var DateLabel: UILabel!
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
