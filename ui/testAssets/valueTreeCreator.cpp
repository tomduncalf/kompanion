juce::Array<juce::var> array { juce::var{"Test"}, juce::var{1234}, juce::var{true} };

juce::ValueTree tree {"TestTree"};
tree.setProperty("stringProperty", "Test", nullptr);
tree.setProperty("intProperty", 1234, nullptr);
tree.setProperty("int64Property", (int64_t) 9223372036854775800, nullptr);
tree.setProperty("boolProperty", true, nullptr);
tree.setProperty("arrayProperty", array, nullptr);

juce::ValueTree childTree1 {"TestChild1"};
childTree1.setProperty("stringProperty", "TestChildProperty", nullptr);
tree.addChild(childTree1, 0, nullptr);

juce::ValueTree nestedChildTree1 {"TestNestedChild1"};
nestedChildTree1.setProperty("stringProperty", "TestNestedChildProperty", nullptr);
childTree1.addChild(nestedChildTree1, 0, nullptr);

juce::ValueTree childTree2 {"TestChild2"};
tree.addChild(childTree2, 1, nullptr);

auto file = juce::File ("/tmp/mo");
file.deleteFile();

juce::FileOutputStream o { file };
tree.writeToStream(o);
o.flush();