Pod::Spec.new do |s|
  s.name             = "GTToolBox"
  s.version          = "1.2.4"
  s.summary          = "iOS App ToolBox"
  s.description      = <<-DESC
                          GTToolBox is a iOS tool library .
                       DESC
  s.homepage         = "https://github.com/GeenTi/GTToolBox/tree/master"
  # s.screenshots      = "www.example.com/screenshots_1", "www.example.com/screenshots_2"
  s.license          = 'MIT'
  s.author           = { "GeenTi" => "dev@geenti.com" }
  s.source           = { :git => "https://github.com/GeenTi/GTToolBox.git", :tag => s.version }
  # s.social_media_url = 'https://twitter.com/NAME'

  s.platform     = :ios
  s.ios.deployment_target = '12.0'
  s.requires_arc = true

  s.source_files = 'GTToolBox/**/*.{h,m,mm,c}'
  s.public_header_files = 'GTToolBox/**/*.h'   #公开头文件地址
  s.frameworks = 'UIKit','Foundation','SystemConfiguration','CFNetwork','CoreGraphics','QuartzCore'
  s.libraries = 'c++'
  s.user_target_xcconfig = { 'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES' }
end
