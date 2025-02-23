import common.Review
import common.Constants

// ----------------------------------------------------------------- APK
for(ARCH in Constants.AndroidArchAPKReview)
{

def j = new Review
	(
		name: 'Android_APK_' + ARCH,
		libraries: ['Android_' + ARCH],
		label: 'Android',
		artifacts: 'build/dist/**/AusweisApp2-*.apk*,build/debug.symbols/*'
	).generate(this)


j.with
{
	steps
	{
		shell('cd source; cmake -DCMD=IMPORT_PATCH -P cmake/cmd.cmake')

		shell("cd source; cmake --preset ci-android-apk-review -DCMAKE_ANDROID_ARCH_ABI=${ARCH}")
		shell('cmake --build build')
		shell('cmake --install build')
		shell('cmake --build build --target apk')
		shell('cmake --build build --target verify.signature')
		shell('cmake --build build --target dump.apk')
	}

	publishers {
		recordIssues {
			tools {
				androidLintParser {
					pattern('**/lint-results*.xml')
				}
			}
			qualityGates {
				qualityGate {
					threshold(1)
					type('TOTAL')
					unstable(false)
				}
			}
		}
	}
}

}


// ----------------------------------------------------------------- AAR
def neededLibraries = []
for(ARCH in Constants.AndroidArchAAR)
{
	neededLibraries.add('Android_' + ARCH)
}

def j = new Review
	(
		name: 'Android_AAR',
		libraries: neededLibraries,
		label: 'Android',
		artifacts: 'build/dist/**/ausweisapp-*.aar,build/dist/**/ausweisapp-*.pom,build/dist/**/ausweisapp-*.jar,build/debug.symbols/*'
	).generate(this)

j.with
{
	steps
	{
		shell('cd source; cmake -DCMD=IMPORT_PATCH -P cmake/cmd.cmake')
		shell('cd source; cmake --preset ci-android-aar-review')
		shell('cmake --build build')
		shell('cmake --install build')
		shell('cmake --build build --target aar')
	}

	publishers {
		recordIssues {
			tools {
				androidLintParser {
					pattern('**/lint-results*.xml')
				}
			}
			qualityGates {
				qualityGate {
					threshold(1)
					type('TOTAL')
					unstable(false)
				}
			}
		}
	}
}
