Pod::Spec.new do |spec|
  spec.name         = "GTToolBox"
  spec.version      = "1.1.8"
  spec.summary      = "iOS App ToolBox"
  spec.description  = <<-DESC
                      GTToolBox is a tool library to facilitate the development of their own iOSApp, written in Object-C, only supports iOS10.0 and later.
                   DESC

  spec.homepage     = "https://github.com/GeenTi/GTToolBox/tree/master"
  spec.license      = "MIT (example)"
  spec.author       = { "GeenTi" => "dev@geenti.com" }
  spec.source       = { :git => "https://github.com/GeenTi/GTToolBox.git", :tag => "#{spec.version}" }

  spec.platform        = :ios
  spec.ios.deployment_target = '10.0' #最低要求版本
  spec.requires_arc    = true
  spec.source_files = 'GTToolBox/**/*.{h,m,mm,c}'
  spec.public_header_files = 'GTToolBox/**/*.h'   #公开头文件地址
  spec.frameworks = 'UIKit','Foundation','libc','SystemConfiguration','CFNetwork'

end
