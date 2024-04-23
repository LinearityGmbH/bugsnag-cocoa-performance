//
//  MazeRunnerCommand.swift
//  Fixture
//
//  Created by Karl Stenerud on 16.11.23.
//

import Foundation

class MazeRunnerCommand: Codable {
    let message: String
    let index: Int
    let action: String
    let uuid: String
    let args: Array<String>
    
    init(uuid: String, action: String, args: Array<String>, message: String, index: Int) {
        self.uuid = uuid
        self.message = message
        self.action = action
        self.args = args
        self.index = index
    }

    required init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        self.uuid = try container.decodeIfPresent(String.self, forKey: .uuid) ?? ""
        self.message = try container.decodeIfPresent(String.self, forKey: .message) ?? ""
        self.action = try container.decodeIfPresent(String.self, forKey: .action) ?? ""
        self.args = try container.decodeIfPresent(Array<String>.self, forKey: .args) ?? []
        self.index = try container.decodeIfPresent(Int.self, forKey: .index) ?? -1
    }
}
