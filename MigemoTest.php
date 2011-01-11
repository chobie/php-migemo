<?php
class MigemoTest extends \PHPUnit_Framework_TestCase{


    /**
     * Migemoロードされているかしらべるよ
     */
    public function testMigemoIsLoaded()
    {
        $this->assertEquals(true,extension_loaded("migemo"));
    }

    /**
     * Migemoクラスがあるかしらべるよ
     * @depends testMigemoIsLoaded
     */
    public function testMigemoClassExists()
    {
        $this->assertEquals(true,class_exists("Migemo"));
    }

    /**
     * @depends testMigemoClassExists
     */
    public function testQueryMethodExists()
    {
        $reflection = new \ReflectionClass("Migemo");
        $this->assertEquals(true,$reflection->hasMethod("query"));
    }

    /**
     * @depends testQueryMethodExists
     */
    public function testQuery()
    {
        $migemo = new Migemo();
        $this->assertEquals("(ﾁｮﾋﾞ|チョビ|ちょび|ｃｈｏｂｉ|chobi)",$migemo->query("chobi"));
        unset($migemo);
    }

    /**
     * @depends testQuery
     */
    public function testQueryCycle()
    {
        $migemo = new Migemo();
        for($i = 0; $i < 30; $i++){
            $this->assertEquals("(ﾁｮﾋﾞ|チョビ|ちょび|ｃｈｏｂｉ|chobi)",$migemo->query("chobi"));
        }
        unset($migemo);

    }
}