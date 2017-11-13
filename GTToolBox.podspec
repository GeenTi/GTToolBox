Pod::Spec.new do |s|
  s.name             = "GTToolBox"
  s.version          = "1.0.0"
  s.summary          = "iOS App ToolBox"
  s.description      = <<-DESC
                       GTToolBox is a tool library to facilitate the development of their own iOSApp, written in Object-C, only supports iOS10.0 and later.
                       DESC
  s.homepage         = "https://github.com/GeenTi/GTToolBox/tree/master"
  # s.screenshots      = "www.example.com/screenshots_1", "www.example.com/screenshots_2"
  s.license          = 'MIT'
  s.author           = { "GeenTi" => "dev@geenti.com" }
  s.source           = { :git => "https://github.com/GeenTi/GTToolBox.git", :tag => s.version }
  # s.social_media_url = 'https://twitter.com/NAME'

  s.platform     = :ios
  s.ios.deployment_target = '10.0'
  s.requires_arc = true


  # s.public_header_files = 'GTToolBox/GTToolBox.h'
  s.resources = 'GTToolBox/**/*.{h,m,mm,c}'
  # s.vendored_frameworks = 'GTToolBox.framework'
  # => 系统依赖类
  s.frameworks = 'Foundation','UIKit','CoreGraphics'
  # => 第三方类
end
