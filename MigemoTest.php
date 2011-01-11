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
     * @depends testMigemoClassExists
     */
    public function testQuery()
    {
        $this->markTestIncomplete('This test has not been implemented yet.');
    }

    /**
     * @depends testMigemoClassExists
     */
    public function testQueryCycle()
    {
        $this->markTestIncomplete('This test has not been implemented yet.');
    }
}