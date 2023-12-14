plugins {
    kotlin("jvm") version "1.9.21"
    kotlin("plugin.serialization") version "1.9.21"
    antlr
}

group = "io.github.linhelurking"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    antlr("org.antlr:antlr4:4.13.1")
    implementation("org.jetbrains.kotlinx:kotlinx-coroutines-core:1.8.0-RC")
    implementation("org.jetbrains.kotlinx:kotlinx-serialization-json:1.6.2")
    testImplementation("org.jetbrains.kotlin:kotlin-test")
}

tasks.test {
    useJUnitPlatform()
}

tasks.generateGrammarSource {
    val pkgPath = "io/github/linhelurking/meta_lang"
    val pkgGroup = "io.github.linhelurking.meta_lang"
    arguments.plusAssign(listOf("-package", pkgGroup, "-visitor"))

    doLast {
        copy {
            from("build/generated-src/antlr/main/")
            include("*.*")
            into("build/generated-src/antlr/main/$pkgPath/")
        }

        fileTree("build/generated-src/antlr/main/") {
            include("*.*")
            delete(this)
        }
    }
}

tasks.compileKotlin {
    dependsOn(tasks.generateGrammarSource)
}

tasks.compileTestKotlin {
    dependsOn(tasks.generateTestGrammarSource)
}

kotlin {
    jvmToolchain(17)
}